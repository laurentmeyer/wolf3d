#ifndef WORLD_H
# define WORLD_H

# include "wolf3d.h"
# include "transform.h"
# include "geometry.h"

# define MAP_EMPTY -2
# define MAP_WALL 20 //14

typedef struct		s_world
{
	char			*map;
	int				map_w;
	int				map_h;
	t_transform		player;
}					t_world;

#endif