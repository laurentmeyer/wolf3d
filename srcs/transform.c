/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:26:04 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 19:26:55 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "input.h"
#include "transform.h"
#include "ft_math.h"

t_transform	translate(t_transform t, t_v2 v)
{
	t_v2	move;

	move.x = v.x * cos(t.degrees * DEG_TO_RAD) - v.y *
		sin(t.degrees * DEG_TO_RAD);
	move.y = -v.y * cos(t.degrees * DEG_TO_RAD) - v.x *
		sin(t.degrees * DEG_TO_RAD);
	t.pos.x += move.x;
	t.pos.y += move.y;
	return (t);
}

void		rotate(t_transform *transform, float degrees)
{
	transform->degrees = normalize_degrees(transform->degrees + degrees);
}
