#include "wolf3d.h"
#include <fcntl.h>
#include <unistd.h>

void		fill_map(t_ram *ram, int y, char *line)
{
	int	x;

	x = 0;
	while (x < MAX_MAP_WIDTH && '\0' != line[x])
	{
		if (0 == x || MAX_MAP_WIDTH - 1 == x || 0 == y || MAX_MAP_HEIGHT - 1 == y)
			ram->world->map[x + MAX_MAP_WIDTH * y] = 1;
		else
			ram->world->map[x + MAX_MAP_WIDTH * y] = (line[x] == 'W') ? 1 : 0;
		++x;
	}
}

void	init_map(t_ram *ram)
{
	int fd;
	char *line;
	int gnl;
	int y;

	if (!(ram->world->map = (char *)malloc(MAX_MAP_HEIGHT * MAX_MAP_WIDTH)))
		exit_message(ram, ERROR, "Could not initialize map\n");
	if (ERROR == (fd = open("test.map", O_RDONLY)))
		exit_message(ram, ERROR, "Could not open map file\n");
	y = 0;
	while (y < MAX_MAP_HEIGHT)
	{
		if ((gnl = gnlite(fd, &line)) < 0)
			exit_message(ram, ERROR, "Could not read map file with gnl\n");
		if (gnl > 0)
			fill_map(ram, y, line);
		free(line);
		if (0 == gnl)
			break;
		y++;
	}
	close(fd);
}

void init_world(t_ram *ram)
{
	if (NULL == (ram->world = (t_world *)malloc(sizeof(t_world))))
		exit_message(ram, ERROR, "Could not initialize world\n");
	ft_bzero(ram->world, sizeof(t_world));
	init_map(ram);
	ram->world->player.pos = (t_v2){32.0, 32.0};
	ram->world->player.angle = 0;
}

void	free_world(t_world *world)
{
	if (NULL != world->map)
		free (world->map);
	free(world);
}