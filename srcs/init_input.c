/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:36:48 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 18:01:35 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "input.h"

void	init_input(t_ram *ram)
{
	if (NULL == (ram->input = (t_input *)malloc(sizeof(t_input))))
		exit_message(ram, ERROR, "Could not allocate ram input\n");
	ft_bzero(ram->input, sizeof(t_input));
	if (NULL == (ram->input->keys_pressed = (int *)malloc(
					(int)KEYBOARD_KEY_COUNT * sizeof(int))))
		exit_message(ram, ERROR, "Could not allocate input key pressed\n");
	ft_bzero(ram->input->keys_pressed, (int)KEYBOARD_KEY_COUNT * sizeof(int));
}

void	free_input(t_input *input)
{
	if (NULL != input->keys_pressed)
		free(input->keys_pressed);
	free(input);
}
