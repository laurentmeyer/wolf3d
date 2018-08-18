#include "wolf3d.h"
#include "assets.h"
#include "display.h"
#include "geometry.h"

/*
** les textures sont stockées colonne par colonne et non ligne par ligne
*/

t_texture		init_texture(t_ram *ram, t_image *img, int id)
{
	t_texture	ret;
	const t_v2i	orig = (t_v2i){(id % 6) * TEX_WIDTH, (id / 6) * TEX_HEIGHT};
	t_v2i		cur;

	if (NULL == (ret = (t_texture)malloc(TEX_WIDTH * TEX_HEIGHT * sizeof(int))))
		exit_message(ram, ERROR, "Could not allocate texture\n");
	ft_bzero(ret, TEX_WIDTH * TEX_HEIGHT * sizeof(int));
	cur = orig;
	while (cur.y - orig.y < TEX_WIDTH)
	{
		cur.x = orig.x;
		while (cur.x - orig.x < TEX_HEIGHT)
		{
			ft_memcpy(ret + TEX_WIDTH * (cur.y - orig.y) + (cur.x - orig.x),
				img->data_addr + img->chars_per_pixel *
				(img->pixels_per_line * cur.y + cur.x), img->chars_per_pixel);
			(cur.x)++;
		}
		(cur.y)++;
	}
	return (ret);
}

void	init_textures(t_ram *ram)
{
	t_image	img;
	int		i;

	if (NULL == (ram->assets->textures = (t_texture *)malloc(TEX_COUNT * sizeof(t_texture))))
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
	while (++i < TEX_COUNT)
		ram->assets->textures[i] = init_texture(ram, &img, i);
	mlx_destroy_image(ram->display->mlx_ptr, img.img_ptr);
}

void		init_assets(t_ram *ram)
{
	if (NULL == (ram->assets = (t_assets *)malloc(sizeof(t_assets))))
		exit_message(ram, ERROR, "Could not initialize assets\n");
	ft_bzero(ram->assets, sizeof(t_assets));
	init_textures(ram);
}

void	free_assets(t_assets *assets)
{
	int	i;

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
	free(assets);
}