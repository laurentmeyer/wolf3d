/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:03:28 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 14:03:57 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int						update_world(t_ram *ram)
{
	apply_user_input(ram);
	return (SUCCESS);
}

int						main_loop(t_ram *ram)
{
	long long			real_time;
	static long long	simulation_time = 0;

	real_time = get_time_us();
	while (simulation_time < real_time)
	{
		update_world(ram);
		simulation_time += ram->timer->delta_time_us;
	}
	render_scene(ram);
	return (SUCCESS);
}
