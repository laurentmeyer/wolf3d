#ifndef RAYCAST_H
# define RAYCAST_H

# include "wolf3d.h"

enum					e_direction
{
	E_VERTICAL,
	E_HORIZONTAL
};

typedef t_transform		t_ray;

typedef struct			s_hit
{
	float				distance;
	int					tex_id;
	float				tex_percent;
}						t_hit;

#endif