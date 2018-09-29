/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_timer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:25:29 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 18:25:38 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "timer.h"

void	init_timer(t_ram *ram)
{
	if (NULL == (ram->timer = (t_timer *)malloc(sizeof(t_timer))))
		exit_message(ram, ERROR, "Could not allocate timer\n");
	ram->timer->delta_time_us = TIMESLICE_US;
}

void	free_timer(t_timer *timer)
{
	free(timer);
}
