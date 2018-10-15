/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:30:19 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 19:40:19 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "ft_math.h"
#include <math.h>

void					raycast_each_col(t_ram *ram)
{
	int					i;
	t_ray				ray;

	ft_bzero(ram->render->hits, ram->display->fps_img->w * sizeof(t_hit));
	i = 0;
	while (i < ram->display->fps_img->w)
	{
		ray.pos = ram->world->player.pos;
		ray.degrees = normalize_degrees(ram->world->player.degrees -
			((float)i * 2.0 / ram->display->fps_img->w - 1.0) * H_FOV / 2.0);
		(ram->render->hits)[i] = raycast(ram, ray);
		++i;
	}
}

void					render_each_ray(t_ram *ram, t_image *img)
{
	int					i;
	t_v2i				player;
	t_v2i				hit;

	player = (t_v2i){(int)(ram->world->player.pos.x * MMAP_PXPM),
		(int)(ram->world->player.pos.y * MMAP_PXPM)};
	i = 0;
	while (i < ram->display->fps_img->w)
	{
		hit = (t_v2i){(int)(((ram->render->hits)[i]).pos.x * MMAP_PXPM),
			(int)(((ram->render->hits)[i]).pos.y * MMAP_PXPM)};
		trace_line(img, player, hit, 0xFF);
		++i;
	}
}

void					draw_minimap(t_ram *ram, t_image *img)
{
	ft_memcpy(img->data_addr, ram->assets->map_layout, MMAP_PXPM *
			MMAP_PXPM * ram->world->map_h * ram->world->map_w * sizeof(int));
}

void					clear_img(void *mlx_ptr, t_image *img)
{
	const unsigned int	ceiling = mlx_get_color_value(mlx_ptr, SKY_COLOR);
	const unsigned int	ground = mlx_get_color_value(mlx_ptr, GROUND_COLOR);
	const size_t		i = img->size_line * img->h / 2;

	ft_memset(img->data_addr, ceiling, i);
	ft_memset(img->data_addr + i, ground, i);
}

int						render_scene(t_ram *ram)
{
	clear_img(ram->display->mlx_ptr, ram->display->fps_img);
	draw_minimap(ram, ram->display->map_img);
	raycast_each_col(ram);
	render_each_col(ram, ram->display->fps_img);
	render_each_ray(ram, ram->display->map_img);
	mlx_put_image_to_window(ram->display->mlx_ptr,
			ram->display->map_win->win_ptr, ram->display->map_img->img_ptr,
			0, 0);
	mlx_put_image_to_window(ram->display->mlx_ptr,
			ram->display->fps_win->win_ptr, ram->display->fps_img->img_ptr,
			0, 0);
	return (SUCCESS);
}
