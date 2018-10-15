/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:48:21 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 17:36:48 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "assets.h"
#include "display.h"
#include "geometry.h"

t_texture		init_texture(t_ram *ram, t_image *img, int id)
{
	t_texture	ret;
	t_v2i		orig;
	t_v2i		cur;

	orig = (t_v2i){(id % 6) * (int)TEX_WIDTH, (id / 6) *
		(int)TEX_HEIGHT};
	if (NULL == (ret = (t_texture)malloc((int)TEX_WIDTH * (int)TEX_HEIGHT *
					sizeof(int))))
		exit_message(ram, ERROR, "Could not allocate texture\n");
	ft_bzero(ret, (int)TEX_WIDTH * (int)TEX_HEIGHT * sizeof(int));
	cur = orig;
	while (cur.x - orig.x < (int)TEX_WIDTH)
	{
		cur.y = orig.y;
		while (cur.y - orig.y < (int)TEX_HEIGHT)
		{
			ft_memcpy(ret + (int)TEX_WIDTH * (cur.x - orig.x) +
					(cur.y - orig.y), img->data_addr + img->chars_per_pixel *
				(img->pixels_per_line * cur.y + cur.x), img->chars_per_pixel);
			(cur.y)++;
		}
		(cur.x)++;
	}
	return (ret);
}

void			init_textures(t_ram *ram)
{
	t_image		img;
	int			i;

	if (NULL == (ram->assets->textures = (t_texture *)malloc((int)TEX_COUNT *
					sizeof(t_texture))))
		exit_message(ram, ERROR, "Could not initialize textures array\n");
	ft_bzero(ram->assets->textures, TEX_COUNT * sizeof(t_texture));
	if (NULL == (img.img_ptr = mlx_xpm_file_to_image(ram->display->mlx_ptr,
		TEX_FILENAME, &(img.w), &(img.h))))
		exit_message(ram, ERROR, "Could not read textures file\n");
	img.data_addr = mlx_get_data_addr(img.img_ptr, &(img.bits_per_pixel),
		&(img.size_line), &(img.endian));
	img.chars_per_pixel = img.bits_per_pixel / 8;
	img.pixels_per_line = img.size_line / img.chars_per_pixel;
	i = -1;
	while (++i < (int)TEX_COUNT)
		ram->assets->textures[i] = init_texture(ram, &img, i);
	mlx_destroy_image(ram->display->mlx_ptr, img.img_ptr);
}

void			init_map_layout(t_ram *ram)
{
	int			i;
	int			j;
	int			c;

	if (NULL == (ram->assets->map_layout = (int *)malloc((int)MMAP_PXPM *
		(int)MMAP_PXPM * ram->world->map_h * ram->world->map_w * sizeof(int))))
		exit_message(ram, ERROR, "Could not initialize minimap template\n");
	ft_bzero(ram->assets->map_layout, MMAP_PXPM * MMAP_PXPM *
		ram->world->map_h * ram->world->map_w * sizeof(int));
	i = -1;
	while (i++ < ram->world->map_h * (int)MMAP_PXPM)
	{
		j = -1;
		while (j++ < ram->world->map_w * (int)MMAP_PXPM)
		{
			c = (ram->world->map)[ram->world->map_w * (i / (int)MMAP_PXPM)
				+ (j / (int)MMAP_PXPM)];
			if (TEX_EMPTY == c)
				(ram->assets->map_layout)[ram->world->map_w * i
					* (int)MMAP_PXPM + j] = 0x383838;
			else
				(ram->assets->map_layout)[ram->world->map_w * i
					* (int)MMAP_PXPM + j] = 0x707070;
		}
	}
}

void			init_assets(t_ram *ram)
{
	if (NULL == (ram->assets = (t_assets *)malloc(sizeof(t_assets))))
		exit_message(ram, ERROR, "Could not initialize assets\n");
	ft_bzero(ram->assets, sizeof(t_assets));
	init_textures(ram);
	init_map_layout(ram);
}

void			free_assets(t_assets *assets)
{
	int			i;

	if (NULL != assets->textures)
	{
		i = 0;
		while (i < TEX_COUNT)
		{
			if (NULL != (assets->textures)[i])
				free((assets->textures)[i]);
			i++;
		}
		free(assets->textures);
	}
	if (NULL != assets->map_layout)
		free(assets->map_layout);
	free(assets);
}
