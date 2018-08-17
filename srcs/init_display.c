#include "wolf3d.h"
#include "display.h"

t_image		*init_image(t_ram *ram, int w, int h)
{
	t_image	*img;

	if (NULL == (img = (t_image *)malloc(sizeof(t_image))))
		exit_message(ram, ERROR, "Could not allocate display image");
	ft_bzero(img, sizeof(t_image));
	if (NULL == (img->img_ptr = mlx_new_image(ram->display->mlx_ptr, w, h)))
		exit_message(ram, ERROR, "Could not allocate mlx image");
	if (NULL == (img->data_addr = mlx_get_data_addr(img->img_ptr,
		&(img->bits_per_pixel), &(img->size_line), &(img->endian))))
		exit_message(ram, ERROR, "Could not get mlx data address");
	img->chars_per_pixel = img->bits_per_pixel / 8;
	img->pixels_per_line = img->size_line / img->chars_per_pixel;
	img->w = w;
	img->h = h;
	return (img);
}

t_window	*init_window(t_ram *ram, int w, int h, char *name)
{
	t_window	*win;

	if (NULL == (win = (t_window *)malloc(sizeof(t_window))))
		exit_message(ram, ERROR, "Could not allocate display win");
	ft_bzero(win, sizeof(t_window));
	if (NULL == (win->name = ft_strdup(name)))
		exit_message(ram, ERROR, "Could not duplicate display win name");
	if (NULL == (win->win_ptr = mlx_new_window(ram->display->mlx_ptr, w, h, name)))
		exit_message(ram, ERROR, "Could not allocate mlx window");
	win->w = w;
	win->h = h;
	return (win);
}

void		init_display(t_ram *ram)
{
	t_display	*d;

	if (NULL == (d = (t_display *)malloc(sizeof(t_display))))
		exit_message(ram, ERROR, "Could not allocate display");
	ft_bzero(d, sizeof(t_display));
	if (NULL == (d->mlx_ptr = mlx_init()))
		exit_message(ram, ERROR, "Could not get mlx ptr");
	ram->display = d;
	d->win = init_window(ram, WIN_W, WIN_H, WIN_NAME);
	d->img = init_image(ram, WIN_W, WIN_H);
}

void		free_display(t_display *display)
{
	if (NULL != display->img)
	{
		if (NULL != display->img->img_ptr)
			mlx_destroy_image(display->mlx_ptr, display->img->img_ptr);
		free(display->img);
	}
	if (NULL != display->win)
	{
		if (NULL != display->win->win_ptr)
			mlx_destroy_window(display->mlx_ptr, display->win->win_ptr);
		if (NULL != display->win->name)
			free(display->win->name);
		free(display->win);
	}
	free(display);
}