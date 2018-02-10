#include "wolf3d.h"
#include <stdlib.h>
#include "ft_printf.h" //

#define WIN_H 480
#define WIN_W 640
#define WIN_NAME "wolf3d"

int g_verbose = 1; //

static int		init_framebuf(t_display *display, t_framebuf *f, int width, int height)
{
	if (NULL == (f->img_ptr = mlx_new_image(display->mlx_ptr, width, height)))
		return (ERROR);
	f->data_addr = mlx_get_data_addr(f->img_ptr, &(f->bits_per_pixel),
			&(f->size_line), &(f->endian));
	if (NULL == f->data_addr)
		return (ERROR);
	f->chars_per_pixel = f->bits_per_pixel / 8;
	f->pixels_per_line = f->size_line / f->chars_per_pixel;
	return (SUCCESS);
}

static t_window	init_window(t_display *display)
{
	t_window	window;

	if (NULL == (window = mlx_new_window(display->mlx_ptr, WIN_W, WIN_H, WIN_NAME)))
		return (NULL);
	return (window);
}

int		init_display(t_display *display)
{
	if (NULL == (display->mlx_ptr = mlx_init()))
		return (ERROR); //error handling
	if (NULL == (display->window = init_window(display)))
		return (ERROR);
	if (ERROR == init_framebuf(display, &(display->framebuf), WIN_W,WIN_H))
		return (ERROR);
	display->win_width = WIN_W;
	display->win_height = WIN_H;
	return (SUCCESS);
}

int		init_world(t_ram *ram)
{
	ram->world.map_height = 480;
	ram->world.map_width = 640;
	ram->world.player_pos = (t_vector2){32, 32};
	return (SUCCESS);
}

t_ram	*init_ram(void)
{
	t_ram		*ram;

	if (NULL == (ram = (t_ram *)malloc(sizeof(t_ram))))
		return (NULL);//handle error
	if (ERROR == init_display(&(ram->display)))
		return (NULL);
	init_world(ram);
	return (ram);
}

int main(void)
{
	t_ram *ram;

	if ((ram = init_ram()) == NULL)
		return (1);
	init_hooks(ram);
	mlx_loop(ram->display.mlx_ptr);
	return (0);
}
