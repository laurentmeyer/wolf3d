#include "wolf3d.h"

void pixel_put(t_image *img, int x, int y, unsigned int color)
{
	ft_memcpy(img->data_addr + (img->pixels_per_line * y + x) * img->chars_per_pixel, (const void *)(&color), img->chars_per_pixel);
}

int		clear_img(t_display *display)
{
	const unsigned int	ceiling = mlx_get_color_value(display->mlx_ptr, 0x383838);
	const unsigned int	ground = mlx_get_color_value(display->mlx_ptr, 0x707070);
	const size_t		i = display->img->size_line * display->win->h / 2;

	ft_memset(display->img->data_addr, ceiling, i);
	ft_memset(display->img->data_addr + i, ground, i);
	return (SUCCESS);
}    

int display_img(t_display *display)
{
    mlx_put_image_to_window(display->mlx_ptr, display->win->win_ptr, display->img->img_ptr, 0, 0);
    return (SUCCESS);
}

int		draw_tex_to_img(t_image *img, t_texture tex)//
{
	int x;
	int y;

	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			pixel_put(img, x, y, tex[x * 64 + y]);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int     render_scene(t_ram *ram)
{
	unsigned int color;

    clear_img(ram->display);
	color = mlx_get_color_value(ram->display->mlx_ptr, 0xffff);
	draw_tex_to_img(ram->display->img, ram->assets->textures[9]); //
    pixel_put(ram->display->img, ram->world->player.pos.x, ram->world->player.pos.y, color);
	display_img(ram->display);
    return (SUCCESS);
}
