#ifndef WORLD_H
# define WORLD_H

# include "geometry.h"

# define MAX_MAP_HEIGHT 64
# define MAX_MAP_WIDTH 64

typedef struct		s_world
{
	char			walls[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
	t_vector2		player_pos;
	int				player_angle;
}					t_world;

#endif