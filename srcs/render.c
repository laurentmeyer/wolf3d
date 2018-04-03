#include "wolf3d.h"

void pixel_put(t_framebuf framebuf, int x, int y, unsigned int color)
{
	ft_memcpy(framebuf.data_addr + (framebuf.pixels_per_line * y + x) * framebuf.chars_per_pixel, (const void *)(&color), framebuf.chars_per_pixel);
}

int		clear_framebuf(t_display *display)
{
	const unsigned int	ceiling = mlx_get_color_value(display->mlx_ptr, 0x383838);
	const unsigned int	ground = mlx_get_color_value(display->mlx_ptr, 0x707070);
	const size_t		i = display->framebuf.size_line * display->win_height / 2;

	ft_memset(display->framebuf.data_addr, ceiling, i);
	ft_memset(display->framebuf.data_addr + i, ground, i);
	return (SUCCESS);
}    

int display_framebuf(t_display display)
{
    mlx_put_image_to_window(display.mlx_ptr, display.window, display.framebuf.img_ptr, 0, 0);
    return (SUCCESS);
}

int		draw_tex_to_framebuf(t_framebuf framebuf, t_texture tex)//
{
	int x;
	int y;
	int	*data_addr;

	data_addr = (int *)mlx_get_data_addr(tex.lit, &x, &y, &x);
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			pixel_put(framebuf, x, y, (unsigned int)data_addr[y * 64 + x]);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int     render_scene(t_ram *ram)
{
	unsigned int color;

    clear_framebuf(&(ram->display));
	color = mlx_get_color_value(ram->display.mlx_ptr, 0xffff);
	draw_tex_to_framebuf(ram->display.framebuf, ram->assets.textures.wall); //
    pixel_put(ram->display.framebuf, ram->world.player.pos.x, ram->world.player.pos.y, color);
	display_framebuf(ram->display);
    return (SUCCESS);
}
