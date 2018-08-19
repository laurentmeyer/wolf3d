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

	adj = (int)(ray.pos.x) + 1.0 - ray.pos.x;
	hit.pos.x = ray.pos.x + adj * tan((90.0 - ray.degrees) * DEG_TO_RAD);
	hit.pos.y = (int)(ray.pos.y);
	while (hit.pos.y + 1.0 < ram->world->map_h && hit.pos.x >= 0.0 && hit.pos.x < (float)ram->world->map_w
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(hit.pos.y + 1.0) * ram->world->map_w + (int)(hit.pos.x)]))
	{
		hit.pos.x -= tan((90.0 - ray.degrees) * DEG_TO_RAD);
		hit.pos.y += 1.0;
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, hit.pos);
	hit.tex_percent = (int)(hit.pos.x + 1.0) - hit.pos.x;
	return (hit);
}

static t_hit	raycast_horizontal_north(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;

	adj = ray.pos.x - (int)(ray.pos.x);
	hit.pos.x = ray.pos.x - adj * tan((90.0 - ray.degrees) * DEG_TO_RAD);
	hit.pos.y = (int)(ray.pos.y);
	while (hit.pos.y - 1.0 >= 0.0 && hit.pos.x >= 0.0 && hit.pos.x < (float)ram->world->map_w
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(hit.pos.y - 1.0) * ram->world->map_w + (int)(hit.pos.x)]))
	{
		hit.pos.x += tan((90.0 - ray.degrees) * DEG_TO_RAD);
		hit.pos.y -= 1.0;
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, hit.pos);
	hit.tex_percent = hit.pos.x - (int)(hit.pos.x);
	return (hit);
}

static t_hit	raycast_vertical_east(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;

	adj = (int)(ray.pos.x) + 1.0 - ray.pos.x;
	hit.pos.x = (float)((int)(ray.pos.x) + 1);
	hit.pos.y = ray.pos.y - adj * tan(ray.degrees * DEG_TO_RAD);
	hit.tex_id = MAP_EMPTY;
	while (hit.pos.x + 1.0 < (float)ram->world->map_w && hit.pos.y >= 0.0 && hit.pos.y < (float)ram->world->map_h
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(hit.pos.y) * ram->world->map_w + (int)(hit.pos.x + 1.0)]))
	{
		hit.pos.x += 1.0;
		hit.pos.y -= tan(ray.degrees * DEG_TO_RAD);
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, hit.pos);
	hit.tex_percent = (int)(hit.pos.y) + 1.0 - hit.pos.y;
	return (hit);
}

static t_hit	raycast_vertical_west(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;

	adj = ray.pos.x - (int)(ray.pos.x);
	hit.pos.x = (int)(ray.pos.x);
	hit.pos.y = ray.pos.y + adj * tan(ray.degrees * DEG_TO_RAD);
	hit.tex_id = MAP_EMPTY;
	while (hit.pos.x >= 1.0 && hit.pos.y >= 0.0 && hit.pos.y < (float)ram->world->map_h
		&& MAP_EMPTY == (hit.tex_id = (ram->world->map)[(int)(hit.pos.y) * ram->world->map_w + (int)(hit.pos.x - 1.0)]))
	{
		hit.pos.x -= 1.0;
		hit.pos.y += tan(ray.degrees * DEG_TO_RAD);
	}
	if (MAP_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ray, hit.pos);
	hit.tex_percent = hit.pos.y - (int)(hit.pos.y);
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