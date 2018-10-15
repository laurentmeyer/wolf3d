/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:04:40 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 18:04:50 by lcharvol         ###   ########.fr       */
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
