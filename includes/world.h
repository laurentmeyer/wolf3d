#ifndef WORLD_H
# define WORLD_H

# include "wolf3d.h"
# include "geometry.h"

typedef struct		s_world
{
	int				map_height;
	int				map_width;
	t_vector2		player_pos;
	int				player_angle;
}					t_world;

#endif