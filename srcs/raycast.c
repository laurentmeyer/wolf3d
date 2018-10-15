/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:49:30 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 13:00:17 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "assets.h"
#include "raycast.h"
#include "ft_math.h"

float		projected_distance(t_ram *ram, t_v2 pos)
{
	return ((pos.x - ram->world->player.pos.x) * cos(ram->world->player.degrees
				* DEG_TO_RAD)
		- (pos.y - ram->world->player.pos.y) * sin(ram->world->player.degrees
			* DEG_TO_RAD));
}

t_hit		raycast_horizontal_south(t_ram *ram, t_ray ray)
{
	float	opp;
	t_hit	hit;

	opp = (int)(ray.pos.y) + 1.0 - ray.pos.y;
	hit.pos.x = ray.pos.x - opp / tan(ray.degrees * DEG_TO_RAD);
	hit.pos.y = (int)(ray.pos.y + 1.0);
	hit.tex_id = TEX_EMPTY;
	while (hit.pos.x >= 0.0 && hit.pos.x < (float)ram->world->map_w
		&& TEX_EMPTY == (hit.tex_id = (ram->world->map)[(int)(hit.pos.y) *
			ram->world->map_w + (int)(hit.pos.x)]))
	{
		hit.pos.x -= tan((90.0 - ray.degrees) * DEG_TO_RAD);
		hit.pos.y += 1.0;
	}
	hit.distance = projected_distance(ram, hit.pos);
	hit.tex_percent = (int)(hit.pos.x + 1.0) - hit.pos.x;
	hit.direction = E_HIT_SOUTH;
	return (hit);
}

t_hit		raycast_horizontal_north(t_ram *ram, t_ray ray)
{
	float	opp;
	t_hit	hit;

	opp = ray.pos.y - (int)(ray.pos.y);
	hit.pos.x = ray.pos.x + opp / tan(ray.degrees * DEG_TO_RAD);
	hit.pos.y = (int)(ray.pos.y);
	hit.tex_id = TEX_EMPTY;
	while (hit.pos.y - 1.0 >= 0.0 && hit.pos.x >= 0.0 && hit.pos.x <
			(float)ram->world->map_w && TEX_EMPTY == (hit.tex_id =
				(ram->world->map)[(int)(hit.pos.y - 1.0) * ram->world->map_w
				+ (int)(hit.pos.x)]))
	{
		hit.pos.x += tan((90.0 - ray.degrees) * DEG_TO_RAD);
		hit.pos.y -= 1.0;
	}
	hit.distance = projected_distance(ram, hit.pos);
	hit.tex_percent = hit.pos.x - (int)(hit.pos.x);
	hit.direction = E_HIT_NORTH;
	return (hit);
}

t_hit		raycast_vertical_east(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;

	adj = (int)(ray.pos.x) + 1.0 - ray.pos.x;
	hit.pos.x = (float)((int)(ray.pos.x) + 1);
	hit.pos.y = ray.pos.y - adj * tan(ray.degrees * DEG_TO_RAD);
	hit.tex_id = TEX_EMPTY;
	while (hit.pos.y >= 0.0 && hit.pos.y < (float)ram->world->map_h
		&& TEX_EMPTY == (hit.tex_id = (ram->world->map)[(int)(hit.pos.y)
			* ram->world->map_w + (int)(hit.pos.x)]))
	{
		hit.pos.x += 1.0;
		hit.pos.y -= tan(ray.degrees * DEG_TO_RAD);
	}
	if (TEX_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ram, hit.pos);
	hit.direction = E_HIT_EAST;
	hit.tex_percent = hit.pos.y - (int)(hit.pos.y);
	return (hit);
}

t_hit		raycast_vertical_west(t_ram *ram, t_ray ray)
{
	float	adj;
	t_hit	hit;

	adj = ray.pos.x - (int)(ray.pos.x);
	hit.pos.x = (int)(ray.pos.x);
	hit.pos.y = ray.pos.y + adj * tan(ray.degrees * DEG_TO_RAD);
	hit.tex_id = TEX_EMPTY;
	while (hit.pos.x >= 1.0 && hit.pos.y >= 0.0 && hit.pos.y <
			(float)ram->world->map_h && TEX_EMPTY == (hit.tex_id =
				(ram->world->map)[(int)(hit.pos.y)
				* ram->world->map_w + (int)(hit.pos.x - 1.0)]))
	{
		hit.pos.x -= 1.0;
		hit.pos.y += tan(ray.degrees * DEG_TO_RAD);
	}
	if (TEX_EMPTY != hit.tex_id)
		hit.tex_id += 1;
	hit.distance = projected_distance(ram, hit.pos);
	hit.direction = E_HIT_WEST;
	hit.tex_percent = (int)(hit.pos.y) + 1.0 - hit.pos.y;
	return (hit);
}

t_hit		raycast(t_ram *ram, t_ray ray)
{
	t_hit	h_hit;
	t_hit	v_hit;
	int		east;
	int		north;

	north = ray.degrees <= 180.0;
	east = ray.degrees <= 90.0 || ray.degrees >= 270.0;
	if (ray.degrees == 90.0 || ray.degrees == 270.0)
		return (north ? raycast_horizontal_north(ram, ray) :
				raycast_horizontal_south(ram, ray));
	else if (ray.degrees == 0.0 || ray.degrees == 180.0)
	{
		return (east ? raycast_vertical_east(ram, ray)
				: raycast_vertical_west(ram, ray));
	}
	h_hit = north ? raycast_horizontal_north(ram, ray)
		: raycast_horizontal_south(ram, ray);
	v_hit = east ? raycast_vertical_east(ram, ray)
		: raycast_vertical_west(ram, ray);
	return (TEX_EMPTY != h_hit.tex_id && h_hit.distance
			< v_hit.distance ? h_hit : v_hit);
}
