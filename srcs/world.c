#include "wolf3d.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

int fill_map(t_ram *ram, int y, char *line)
{
	int	x;

	x = 0;
	while (x < MAX_MAP_WIDTH && '\0' != line[x])
	{
		if (0 == x || MAX_MAP_WIDTH - 1 == x || 0 == y || MAX_MAP_HEIGHT - 1 == y)
			ram->world.walls[x][y] = 1;
		else
			ram->world.walls[x][y] = line[x] == 'W' ? 1 : 0;
		++x;
	}
	return (SUCCESS);
}

int init_map(t_ram *ram)
{
	int fd;
	char *line;
	int gnl;
	int y;

	if (ERROR == (fd = open("test.map", O_RDONLY)))
		return (ERROR);
	y = 0;
	while (MAX_MAP_HEIGHT > y)
	{
		if (0 > (gnl = gnlite(fd, &line)))
			return (ERROR);
		if (0 == gnl)
		{
			free(line);
			break;
		}
		fill_map(ram, y, line);
		free(line);
		y++;
	}
	close(fd);
	return (SUCCESS);
}

void print_map(t_ram *ram)
{
	int x = 0;
	int y = 0;

	while (y < MAX_MAP_HEIGHT)
	{
		x = 0;
		while (x < MAX_MAP_WIDTH)
		{
			ft_printf("%d", ram->world.walls[x][y]);
			++x;
		}
		ft_printf("\n");
		y++;
	}
}

int init_world(t_ram *ram)
{
	if (ERROR == init_map(ram))
		return (ERROR);
	ram->world.player.pos = (t_v2){32.0, 32.0};
	ram->world.player.angle = 0;
	return (SUCCESS);
}