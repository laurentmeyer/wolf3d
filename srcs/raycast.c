#include "wolf3d.h"
#include "assets.h"
#include "raycast.h"
#include "ft_math.h"

float			projected_distance(t_transform player, t_v2 pos)
{
	return (abs_float(pos.x - player.pos.x) * cos(player.degrees * DEG_TO_RAD)
		- abs_float(pos.y - player.pos.y) * sin(player.degrees * DEG_TO_RAD));
}

static t_hit	raycast_horizontal_south(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;
	t_v2	pos;

	adj = (int)(ray.pos.x) + 1.0 - ray.pos.x;
	pos.x = ray.pos.x + adj * tan((90.0 - ray.degrees) * DEG_TO_RAD);
	pos.y = (int)(ray.pos.y);
	while (pos.y + 1.0 < MAX_MAP_HEIGHT && pos.x >= 0.0 && pos.x < (float)MAX_MAP_WIDTH
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(pos.y + 1.0) * MAX_MAP_WIDTH + (int)(pos.x)]))
	{
		pos.x -= tan((90.0 - ray.degrees) * DEG_TO_RAD);
		pos.y += 1.0;
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, pos);
	hit.tex_percent = (int)(pos.x + 1.0) - pos.x;
	return (hit);
}

static t_hit	raycast_horizontal_north(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;
	t_v2	pos;

	adj = ray.pos.x - (int)(ray.pos.x);
	pos.x = ray.pos.x - adj * tan((90.0 - ray.degrees) * DEG_TO_RAD);
	pos.y = (int)(ray.pos.y);
	while (pos.y - 1.0 >= 0.0 && pos.x >= 0.0 && pos.x < (float)MAX_MAP_WIDTH
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(pos.y - 1.0) * MAX_MAP_WIDTH + (int)(pos.x)]))
	{
		pos.x += tan((90.0 - ray.degrees) * DEG_TO_RAD);
		pos.y -= 1.0;
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, pos);
	hit.tex_percent = pos.x - (int)(pos.x);
	return (hit);
}

// static t_hit	raycast_vertical_east(t_ram *ram, t_ray ray)
// {
// 	float	adj;
// 	t_hit	hit;
// 	t_v2	pos;
// 	t_v2i	square;

// 	adj = (int)(ray.pos.x) + 1.0 - ray.pos.x;
// 	square.x = 1 + (int)(ray.pos.x);
// 	pos.x = (float)(square.x);
// 	pos.y = ray.pos.y - adj * tan(ray.degrees * DEG_TO_RAD);
// 	square.y = (int)(pos.y);
// 	while (0 == (hit.tex_id = (ram->world->map)[square.y * MAX_MAP_WIDTH + square.x]))
// 	{
// 		square.x += 1;
// 		pos.x = (float)(square.x);
// 		pos.y -= tan(ray.degrees * DEG_TO_RAD);
// 		square.y = (int)(pos.y);
// 	}
// 	hit.tex_id += 1;
// 	hit.distance = projected_distance(ray, pos);
// 	hit.tex_percent = (float)(square.y + 1) - pos.y;
// 	return (hit);
// }

static t_hit	raycast_vertical_east(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;
	t_v2	pos;

	adj = (int)(ray.pos.x) + 1.0 - ray.pos.x;
	pos.x = (float)((int)(ray.pos.x) + 1);
	pos.y = ray.pos.y - adj * tan(ray.degrees * DEG_TO_RAD);
	hit.tex_id = MAP_EMPTY;
	while (pos.x + 1.0 < (float)MAX_MAP_WIDTH && pos.y >= 0.0 && pos.y < (float)MAX_MAP_HEIGHT
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(pos.y) * MAX_MAP_WIDTH + (int)(pos.x + 1.0)]))
	{
		pos.x += 1.0;
		pos.y -= tan(ray.degrees * DEG_TO_RAD);
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, pos);
	hit.tex_percent = (int)(pos.y) + 1.0 - pos.y;
	return (hit);
}

static t_hit	raycast_vertical_west(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;
	t_v2	pos;

	adj = ray.pos.x - (int)(ray.pos.x);
	pos.x = (int)(ray.pos.x);
	pos.y = ray.pos.y + adj * tan(ray.degrees * DEG_TO_RAD);
	hit.tex_id = MAP_EMPTY;
	while (pos.x >= 1.0 && pos.y >= 0.0 && pos.y < (float)MAX_MAP_HEIGHT
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(pos.y) * MAX_MAP_WIDTH + (int)(pos.x - 1.0)]))
	{
		pos.x -= 1.0;
		pos.y += tan(ray.degrees * DEG_TO_RAD);
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, pos);
	hit.tex_percent = pos.y - (int)(pos.y);
	return (hit);
}

t_hit			raycast(t_ram *ram, t_ray ray)
{
	t_hit	h_hit;
	t_hit	v_hit;
	int		east;
	int		north;

	north = ray.degrees <= 180.0;
	east = ray.degrees <= 90.0 || ray.degrees >= 270.0;
	if (ray.degrees == 90.0 || ray.degrees == 270.0)
		return (north ? raycast_horizontal_north(ram, ray) : raycast_horizontal_south(ram, ray));
	else if (ray.degrees == 0.0 || ray.degrees == 180.0)
		return (east ? raycast_vertical_east(ram, ray) : raycast_vertical_west(ram, ray));
	h_hit = north ? raycast_horizontal_north(ram, ray) : raycast_horizontal_south(ram, ray);
	v_hit = east ? raycast_vertical_east(ram, ray) : raycast_vertical_west(ram, ray);
	return (MAP_EMPTY != h_hit.tex_id && h_hit.distance < v_hit.distance ? h_hit : v_hit);
}