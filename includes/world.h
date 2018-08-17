#ifndef WORLD_H
# define WORLD_H

# include "wolf3d.h"
# include "geometry.h"
# include "player.h"

# define MAX_MAP_HEIGHT 64
# define MAX_MAP_WIDTH 64

typedef struct		s_world
{
	char			*map;
	t_player		player;
}					t_world;

#endif