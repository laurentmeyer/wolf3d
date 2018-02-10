#include "wolf3d.h"

void pixel_put(t_framebuf framebuf, int x, int y, unsigned int color)
{
	ft_memcpy(framebuf.data_addr + (framebuf.pixels_per_line * y + x) * framebuf.chars_per_pixel, (const void *)(&color), framebuf.chars_per_pixel);
}

int		clear_framebuf(t_display *display)
{
	ft_bzero(display->framebuf.data_addr, display->framebuf.size_line * display->win_height);
	return (SUCCESS);
}    

int display_framebuf(t_display display)
{
    mlx_put_image_to_window(display.mlx_ptr, display.window, display.framebuf.img_ptr, 0, 0);
    return (SUCCESS);
}

int     render_scene(t_ram *ram)
{
	unsigned int color;

    clear_framebuf(&(ram->display));
	color = mlx_get_color_value(ram->display.mlx_ptr, 0xffff);
    pixel_put(ram->display.framebuf, ram->world.player_pos.x, ram->world.player_pos.y, color);
	display_framebuf(ram->display);
    return (SUCCESS);
}
