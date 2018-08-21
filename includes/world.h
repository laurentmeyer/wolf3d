#ifndef WORLD_H
# define WORLD_H

# include "wolf3d.h"
# include "transform.h"
# include "geometry.h"

# define TEX_EMPTY -2
# define TEX_WALL_STONE 0
# define TEX_FLAG_NAZI 4
# define TEX_HITLER_STONE 6
# define TEX_PRISON_EMPTY 8
# define TEX_PRISON_DEAD 12
# define TEX_WALL_BLUE 14
# define TEX_HITLER_WOOD 20
# define TEX_WALL_WOOD 22

typedef struct		s_world
{
	char			*map;
	int				map_w;
	int				map_h;
	t_transform		player;
}					t_world;

#endif