#include "wolf3d.h"
#include "ft_math.h"

void		raycast_each_col(t_ram *ram)
{
	const float	fov = 40.0;
	int			i;
	t_ray		ray;

	ft_bzero(ram->render->hits, ram->display->img->w * sizeof(t_hit));
	i = 0;
	while (i < ram->display->img->w)
	{
		ray.pos = ram->world->player.pos;
		ray.degrees = normalize_degrees(ram->world->player.degrees -
			((float)i * 2.0 / ram->display->img->w - 1.0) * fov / 2.0);
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

	i = 0;
	while (i < ram->display->img->w)
	{
		h = (int)(TEX_HEIGHT / ((ram->render->hits)[i]).distance) & ~1;
		scale_tex(h, buffer,
			(ram->assets->textures)[((ram->render->hits)[i]).tex_id]
			+ (int)(TEX_HEIGHT * ((ram->render->hits)[i]).tex_percent));
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

void		clear_img(void *mlx_ptr, t_image *img)
{
	const unsigned int	ceiling = mlx_get_color_value(mlx_ptr, 0x383838);
	const unsigned int	ground = mlx_get_color_value(mlx_ptr, 0x707070);
	const size_t		i = img->size_line * img->h / 2;

	ft_memset(img->data_addr, ceiling, i);
	ft_memset(img->data_addr + i, ground, i);
}    

int     render_scene(t_ram *ram)
{
    clear_img(ram->display->mlx_ptr, ram->display->img);
	raycast_each_col(ram);
	render_each_col(ram, ram->display->img);
	// pixel_put(ram->display->img, ram->world->player.pos.x, ram->world->player.pos.y, 0xffffff); 
    mlx_put_image_to_window(ram->display->mlx_ptr, ram->display->win->win_ptr,
		ram->display->img->img_ptr, 0, 0);
    return (SUCCESS);
}
