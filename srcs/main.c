#include "wolf3d.h"

int main(void)
{
	t_ram *ram;

	ram = init_ram();
	mlx_loop(ram->display->mlx_ptr);
	return (0);
}