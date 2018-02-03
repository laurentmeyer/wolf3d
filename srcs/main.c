#include "wolf3d.h"
#include <stdlib.h>

#define WIN_H 480
#define WIN_W 640
#define WIN_NAME "wolf3d"

t_ram	*init_ram(void)
{
	t_ram	*ram;

	if ((ram = (t_ram *)malloc(sizeof(t_ram))) != NULL
		&& (ram->mlx_ptr = mlx_init()) != NULL
		&& (ram->win_ptr = mlx_new_window(ram->mlx_ptr, WIN_W, WIN_H, WIN_NAME))
		&& (ram->img_ptr = mlx_new_image(ram->mlx_ptr, WIN_W, WIN_H)) != NULL)
	{
		ram->data_addr = mlx_get_data_addr(ram->img_ptr, &(ram->bits_per_pixel),
			&(ram->size_line), &(ram->endian));
	}
	return (ram);
}

void pixel_put(t_ram *ram, int x, int y, unsigned int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		((unsigned int *)(ram->data_addr))[y * 640 + x] = color;
}

int main(void)
{
	t_ram *ram;
	size_t x;
	size_t y;
	unsigned int color;

	if ((ram = init_ram()) == NULL)
		return (1);
	color = mlx_get_color_value(ram->mlx_ptr, 0xffff);
	y = 0;
	while (y < 300)
	{
		x = 0;
		while (x < 200)
		{
			pixel_put(ram, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(ram->mlx_ptr, ram->win_ptr, ram->img_ptr, 0, 0);
	mlx_loop(ram->mlx_ptr);
	return (0);
}
