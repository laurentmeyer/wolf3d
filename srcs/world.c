#include "wolf3d.h"
#include "ft_printf.h"

void print_map(t_ram *ram)
{
	int x = 0;
	int y = 0;

	while (y < MAX_MAP_HEIGHT)
	{
		x = 0;
		while (x < MAX_MAP_WIDTH)
		{
			ft_printf("%d", ram->world->map[x + MAX_MAP_WIDTH * y]);
			++x;
		}
		ft_printf("\n");
		y++;
	}
}