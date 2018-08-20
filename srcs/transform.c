#include "wolf3d.h"
#include "input.h"
#include "transform.h"
#include "ft_math.h"

void	translate(t_transform *t, t_v2 v)
{
	t_v2	move;
	float	angle;

	angle = (180.0 + t->degrees) * M_PI / 180.0;
	move.x = v.y * sin(angle) - v.x * cos(angle);
	move.y = v.y * cos(angle) + v.x * sin(angle);
	t->pos.x += move.x;
	t->pos.y += move.y;
} 

void	rotate(t_transform *transform, float degrees)
{
	transform->degrees = normalize_degrees(transform->degrees + degrees);
} 