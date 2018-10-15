/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:45:18 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:45:19 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "geometry.h"

# define MOVE_SPEED 0.1
# define ROTATE_SPEED 2

typedef struct	s_transform
{
	t_v2		pos;
	float		degrees;
}				t_transform;

t_transform		translate(t_transform t, t_v2 v);
void			rotate(t_transform *transform, float degrees);

#endif
