/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:30:19 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 17:50:26 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "ft_math.h"
#include <math.h>

void					raycast_straight_col(t_ram *ram)
{
	t_ray				ray;
	t_hit				hit;
	t_v2i				point;
	t_v2i				player;

	player = (t_v2i){(int)(ram->world->player.pos.x * MMAP_PXPM),
		(int)(ram->world->player.pos.y * MMAP_PXPM)};
	ray.pos = ram->world->player.pos;
	ray.degrees = normalize_degrees(ram->world->player.degrees);
	hit = raycast(ram, ray);
	point = (t_v2i){(int)(hit.pos.x * MMAP_PXPM),
					(int)(hit.pos.y * MMAP_PXPM)};
	trace_line(ram->display->map_img, player, point, 0xFF);
}

void					scale_tex(int height, int *dst, int *src)
{
	float				i;
	int					j;
	float				step;

	step = (float)TEX_HEIGHT / (float)height;
	j = 0;
	i = height < WIN_H ? 0.0 : step * (height - WIN_H) / 2;
	while (j < height && j < WIN_H)
	{
		dst[j] = src[(int)i];
		i += step;
		j += 1;
	}
}

void					render_each_col(t_ram *ram, t_image *img)
{
	int					i;
	int					h;
	int					j;
	int					buffer[WIN_H];

	i = 0;
	while (i < ram->display->fps_img->w)
	{
		h = (int)(1000.0 / ((ram->render->hits)[i]).distance) & ~1;
		scale_tex(h, buffer,
				(ram->assets->textures)[((ram->render->hits)[i]).tex_id] +
				TEX_WIDTH * (int)(TEX_HEIGHT *
					((ram->render->hits)[i]).tex_percent));
		h = h > WIN_H ? WIN_H : h;
		j = (WIN_H - h) / 2;
		while (j < (WIN_H + h) / 2)
		{
			pixel_put(img, i, j, buffer[j - (WIN_H - h) / 2]);
			j++;
		}
		++i;
	}
}
