/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ram.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:48:45 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:49:14 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ram	*init_ram(char *file_name)
{
	t_ram *ram;

	if (NULL == (ram = (t_ram *)malloc(sizeof(t_ram))))
		exit_message(ram, ERROR, "Could not initialize RAM\n");
	ft_bzero(ram, sizeof(t_ram));
	ram->file_name = file_name;
	init_world(ram);
	init_display(ram);
	init_assets(ram);
	init_input(ram);
	init_render(ram);
	init_hooks(ram);
	init_timer(ram);
	return (ram);
}

void	free_ram(t_ram *ram)
{
	if (NULL != ram->input)
		free_input(ram->input);
	if (NULL != ram->assets)
		free_assets(ram->assets);
	if (NULL != ram->timer)
		free_timer(ram->timer);
	if (NULL != ram->render)
		free_render(ram->render);
	if (NULL != ram->world)
		free_world(ram->world);
	if (NULL != ram->display)
		free_display(ram->display);
	free(ram);
}
