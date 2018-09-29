/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:25:13 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 19:25:55 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "ft_printf.h"

void	print_map(t_ram *ram)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < ram->world->map_h)
	{
		x = 0;
		while (x < ram->world->map_w)
		{
			ft_printf("%d", ram->world->map[x + ram->world->map_w * y]);
			++x;
		}
		ft_printf("\n");
		y++;
	}
}
