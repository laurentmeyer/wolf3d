#ifndef WORLD_H
# define WORLD_H

# include "geometry.h"
# include "player.h"

# define MAX_MAP_HEIGHT 64
# define MAX_MAP_WIDTH 64

typedef struct		s_world
{
	char			walls[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
	t_player		player;
}					t_world;

#endif