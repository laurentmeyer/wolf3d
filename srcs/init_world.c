#include "wolf3d.h"
#include "world.h"
#include <fcntl.h>
#include <unistd.h>
#include "ft_printf.h"//

void		fill_map(t_ram *ram, int y, char *line)
{
	int		x;
	char	c;

	x = 0;
	while (x < ram->world->map_w && '\0' != line[x])
	{
		if ('B' == line[x])
			c = TEX_WALL_BLUE;
		else if ('S' == line[x])
			c = TEX_HITLER_STONE;
		else if ('F' == line[x])
			c = TEX_FLAG_NAZI;
		else if ('P' == line[x])
			c = TEX_PRISON_EMPTY;
		else if ('D' == line[x])
			c = TEX_PRISON_DEAD;
		else
			c = TEX_EMPTY;
		if (TEX_EMPTY == c && (0 == x || ram->world->map_w - 1 == x || 0 == y
			|| ram->world->map_h - 1 == y))
			c = TEX_WALL_STONE;
		ram->world->map[x + ram->world->map_w * y] = c;
		++x;
	}
	while (x < ram->world->map_w)
		ram->world->map[x++ + ram->world->map_w * y] = TEX_WALL_STONE;
}

void	get_map_dimensions(t_ram *ram, int fd)
{
	char	*line;
	int		gnl;
	char	**split;

	if ((gnl = gnlite(fd, &line)) <= 0)
		exit_message(ram, ERROR, "Could not read map dimensions\n");
	if (NULL == (split = ft_strsplit(line, ' '))
		|| NULL == split[0] || NULL == split[1] || NULL != split[2]
		|| !ft_valid_int_str(split[0], 1) || !ft_valid_int_str(split[1], 1))
		exit_message(ram, ERROR, "Wrong format for map dimensions, must be ints\n");
	ram->world->map_w = ft_atoi(split[0]);
	ram->world->map_h = ft_atoi(split[1]);
	ft_free_strsplit(&split);
	free(line);
}

void	get_player_coords(t_ram *ram, int fd)
{
	char	*line;
	int		gnl;
	char	**split;

	if ((gnl = gnlite(fd, &line)) <= 0)
		exit_message(ram, ERROR, "Could not read player position\n");
	if (NULL == (split = ft_strsplit(line, ' '))
		|| NULL == split[0] || NULL == split[1] || NULL == split[2] || NULL != split[3]
		|| !ft_valid_int_str(split[0], 1) || !ft_valid_int_str(split[1], 1)
		|| !ft_valid_int_str(split[2], 1))
		exit_message(ram, ERROR, "Wrong format for player position, must be ints\n");
	ram->world->player.pos.x = ft_atoi(split[0]);
	ram->world->player.pos.y = ft_atoi(split[1]);
	ram->world->player.degrees = (float)ft_atoi(split[2]);
	ft_free_strsplit(&split);
	free(line);
}

void init_map(t_ram *ram, int fd)
{
	char *line;
	int gnl;
	int y;

	get_map_dimensions(ram, fd);
	get_player_coords(ram, fd);
	if (!(ram->world->map = (char *)malloc(ram->world->map_w * ram->world->map_h)))
		exit_message(ram, ERROR, "Could not initialize map\n");
	y = 0;
	while (y < ram->world->map_h)
	{
		if ((gnl = gnlite(fd, &line)) < 0)
			exit_message(ram, ERROR, "Could not read map file with gnl\n");
		if (gnl > 0)
			fill_map(ram, y, line);
		free(line);
		if (0 == gnl)
			exit_message(ram, ERROR, "Line number is too high\n");
		y++;
	}
}

void init_world(t_ram *ram)
{
	int fd;

	if (NULL == (ram->world = (t_world *)malloc(sizeof(t_world))))
		exit_message(ram, ERROR, "Could not allocate world\n");
	ft_bzero(ram->world, sizeof(t_world));
	if (ERROR == (fd = open("test.map", O_RDONLY)))
		exit_message(ram, ERROR, "Could not open map file\n");
	init_map(ram, fd);
	close(fd);
}

void free_world(t_world *world)
{
	if (NULL != world->map)
		free(world->map);
	free(world);
}