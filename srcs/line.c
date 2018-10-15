/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 13:52:15 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 13:52:20 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

#include <stdio.h>

static void	trace_v_line(t_image *img, t_v2i a, t_v2i b, int color)
{
	if (a.y > b.y)
		trace_v_line(img, b, a, color);
	else
	{
		while (a.y < b.y)
			pixel_put(img, a.x, (a.y)++, color);
	}
}

static void	trace_small_slope(t_image *img, t_v2i a, t_v2i b, int color)
{
	float	slope;
	float	error;

	slope = (float)(b.y - a.y) / (float)(b.x - a.x);
	error = -1.0;
	while (a.x < b.x)
	{
		pixel_put(img, a.x, a.y, color);
		error += fabsf(slope);
		if (error >= 0.0)
		{
			a.y += (slope > 0) ? 1 : -1;
			--error;
		}
		++(a.x);
	}
}

static void	trace_big_slope(t_image *img, t_v2i a, t_v2i b, int color)
{
	float	slope;
	float	error;

	slope = (float)(b.y - a.y) / (float)(b.x - a.x);
	error = -1.0;
	while (a.y < b.y)
	{
		pixel_put(img, a.x, a.y, color);
		error += fabsf(1 / slope);
		if (error >= 0.0)
		{
			a.x += (slope > 0) ? 1 : -1;
			--error;
		}
		++(a.y);
	}
}

void		trace_line(t_image *img, t_v2i a, t_v2i b, int color)
{
	if (a.x == b.x)
		trace_v_line(img, a, b, color);
	else if (fabsf((float)(b.y - a.y) / (float)(b.x - a.x)) > 1.0)
		a.y < b.y ? trace_big_slope(img, a, b, color)
			: trace_big_slope(img, b, a, color);
	else
		a.x < b.x ?
			trace_small_slope(img, a, b, color)
			: trace_small_slope(img, b, a, color);
}
