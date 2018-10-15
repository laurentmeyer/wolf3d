/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:04:23 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 14:04:39 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int argc, char **argv)
{
	t_ram	*ram;

	if (argc < 2)
		exit_message(NULL, ERROR, "wolf3d: No such file\n");
	ram = init_ram(argv[1]);
	mlx_loop(ram->display->mlx_ptr);
	return (0);
}
