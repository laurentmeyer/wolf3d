#ifndef WORLD_H
# define WORLD_H

# include "wolf3d.h"
# include "transform.h"
# include "geometry.h"

# define MAX_MAP_HEIGHT 64
# define MAX_MAP_WIDTH 64

# define MAP_EMPTY -2
# define MAP_WALL 14

typedef struct		s_world
{
	char			*map;
	t_transform		player;
}					t_world;

#endif