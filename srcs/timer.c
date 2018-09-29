/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:27:14 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 19:30:12 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "wolf3d.h"

long long					get_time_us(void)
{
	static struct timespec	start;
	struct timespec			now;
	static int				only_once = 1;
	long long				diff;

	if (only_once)
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		only_once = 0;
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	diff = (now.tv_sec - start.tv_sec) * 1000000;
	diff += (now.tv_nsec - start.tv_nsec) / 1000;
	return (diff);
}
