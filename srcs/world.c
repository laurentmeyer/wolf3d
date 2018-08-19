#include "wolf3d.h"
#include "ft_printf.h"

void print_map(t_ram *ram)
{
	int x = 0;
	int y = 0;

	while (y < ram->world->map_h)
	{
		x = 0;
		while (x < ram->world->map_w)
		{
			ft_printf("%d", ram->world->map[x + ram->world->map_w * y]);
			++x;
		}
		ft_printf("\n");
		y++;
	}
}