/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:45:01 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:45:02 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "wolf3d.h"

typedef enum			e_direction
{
	E_HIT_NORTH,
	E_HIT_SOUTH,
	E_HIT_EAST,
	E_HIT_WEST
}						t_direction;

typedef t_transform		t_ray;

typedef struct			s_hit
{
	t_v2				pos;
	float				distance;
	int					tex_id;
	float				tex_percent;
	t_direction			direction;
}						t_hit;

#endif
