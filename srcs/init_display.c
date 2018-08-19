#include "wolf3d.h"
#include "display.h"
#include "ft_mlx.h"

void		init_display(t_ram *ram)
{
	t_display	*d;

	if (NULL == (d = (t_display *)malloc(sizeof(t_display))))
		exit_message(ram, ERROR, "Could not allocate display\n");
	ft_bzero(d, sizeof(t_display));
	if (NULL == (d->mlx_ptr = mlx_init()))
		exit_message(ram, ERROR, "Could not get mlx ptr\n");
	ram->display = d;
	if (NULL == (d->fps_win = init_window(d->mlx_ptr, WIN_W, WIN_H, WIN_NAME))
		|| NULL == (d->map_win = init_window(d->mlx_ptr, MMAP_PXPM * ram->world->map_w,
			MMAP_PXPM * ram->world->map_h, "minimap")))
		exit_message(ram, ERROR, "Could not init windows\n");
	if (NULL == (d->fps_img = init_image(d->mlx_ptr, WIN_W, WIN_H))
		|| NULL == (d->map_img = init_image(d->mlx_ptr, MMAP_PXPM * ram->world->map_w,
			MMAP_PXPM * ram->world->map_h)))
		exit_message(ram, ERROR, "Could not init images\n");
}

void		free_display(t_display *display)
{
	if (NULL != display->map_img)
		mlx_free_image(display->mlx_ptr, display->map_img);
	if (NULL != display->map_win)
		mlx_free_window(display->mlx_ptr, display->map_win);
	if (NULL != display->fps_img)
		mlx_free_image(display->mlx_ptr, display->fps_img);
	if (NULL != display->fps_win)
		mlx_free_window(display->mlx_ptr, display->fps_win);
	free(display);
}