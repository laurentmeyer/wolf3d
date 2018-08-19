#include "wolf3d.h"
#include "ft_math.h"

void		raycast_each_col(t_ram *ram)
{
	const float	fov = 40.0;
	int			i;
	t_ray		ray;

	ft_bzero(ram->render->hits, ram->display->fps_img->w * sizeof(t_hit));
	i = 0;
	while (i < ram->display->fps_img->w)
	{
		ray.pos = ram->world->player.pos;
		ray.degrees = normalize_degrees(ram->world->player.degrees -
			((float)i * 2.0 / ram->display->fps_img->w - 1.0) * fov / 2.0);
		(ram->render->hits)[i] = raycast(ram, ray);
		++i;
	}
}

void		scale_tex(int height, int *dst, int *src)
{
	int		i;

	i = 0;
	src = 0;
	while (i < height && i < WIN_H)
	{
		dst[i++] = 0xff0000;
	}

}

void		render_each_col(t_ram *ram, t_image *img)
{
	int			i;
	int			h;
	int			j;
	int			buffer[WIN_H];

	float debug[WIN_W];
	int d = -1;
	while (++d < WIN_W)
		debug[d] = ((ram->render->hits)[d]).distance;

	i = 0;
	while (i < ram->display->fps_img->w)
	{
		h = (int)(TEX_HEIGHT / ((ram->render->hits)[i]).distance) & ~1;
		scale_tex(h, buffer,
				  (ram->assets->textures)[((ram->render->hits)[i]).tex_id] + (int)(TEX_HEIGHT * ((ram->render->hits)[i]).tex_percent));
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

void	render_each_ray(t_ram *ram, t_image *img)
{
	int		i;
	t_v2i	player;
	t_v2i	hit;

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

void draw_minimap(t_ram *ram, t_image *img)
{
	ft_memcpy(img->data_addr, ram->assets->map_layout, MMAP_PXPM * MMAP_PXPM *
		ram->world->map_h * ram->world->map_w * sizeof(int));
}

void clear_img(void *mlx_ptr, t_image *img)
{
	const unsigned int ceiling = mlx_get_color_value(mlx_ptr, 0x383838);
	const unsigned int ground = mlx_get_color_value(mlx_ptr, 0x707070);
	const size_t i = img->size_line * img->h / 2;

	ft_memset(img->data_addr, ceiling, i);
	ft_memset(img->data_addr + i, ground, i);
}

int render_scene(t_ram *ram)
{
	clear_img(ram->display->mlx_ptr, ram->display->fps_img);
	draw_minimap(ram, ram->display->map_img);
	raycast_each_col(ram);
	render_each_col(ram, ram->display->fps_img);
	render_each_ray(ram, ram->display->map_img);
	// pixel_put(ram->display->img, ram->world->player.pos.x, ram->world->player.pos.y, 0xffffff);
	mlx_put_image_to_window(ram->display->mlx_ptr, ram->display->map_win->win_ptr,
							ram->display->map_img->img_ptr, 0, 0);
	mlx_put_image_to_window(ram->display->mlx_ptr, ram->display->fps_win->win_ptr,
							ram->display->fps_img->img_ptr, 0, 0);
	return (SUCCESS);
}
