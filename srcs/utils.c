/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:04:40 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 18:36:26 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "assets.h"
#include "raycast.h"
#include "ft_math.h"

int		key_press(int keycode, t_ram *ram)
{
	ram->input->keys_pressed[keycode] = 1;
	return (1);
}

int		key_release(int keycode, t_ram *ram)
{
	ram->input->keys_pressed[keycode] = 0;
	return (1);
}

char	get_tex(t_ram *ram, float x, float y)
{
	return ((ram->world->map)[(int)y * ram->world->map_w + (int)x]);
}

float	projected_distance(t_ram *ram, t_v2 pos)
{
	return ((pos.x - ram->world->player.pos.x) * cos(ram->world->player.degrees
				* DEG_TO_RAD)
		- (pos.y - ram->world->player.pos.y) * sin(ram->world->player.degrees
			* DEG_TO_RAD));
}
