/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:02:09 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 18:25:14 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "render.h"

void	init_render(t_ram *ram)
{
	if (NULL == (ram->render = (t_render *)malloc(sizeof(t_render))))
		exit_message(ram, ERROR, "Could not allocate ram render\n");
	ft_bzero(ram->render, sizeof(t_render));
	if (NULL == (ram->render->hits = (t_hit *)malloc(ram->display->fps_img->w
					* sizeof(t_hit))))
		exit_message(ram, ERROR, "Could not allocate ram hits\n");
	ft_bzero(ram->render->hits, ram->display->fps_img->w * sizeof(t_hit));
}

void	free_render(t_render *render)
{
	if (NULL != render->hits)
		free(render->hits);
	free(render);
}
