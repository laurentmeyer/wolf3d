#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "geometry.h"

typedef struct	s_transform
{
	t_v2		pos;
	float		degrees;
}				t_transform;

t_transform		translate(t_transform t, t_v2 v);
void			rotate(t_transform *transform, float degrees);

#endif