/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:35:30 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 17:35:41 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <unistd.h>

void	exit_message(t_ram *ram, int exit_code, char *message)
{
	if (NULL != ram)
		free_ram(ram);
	if (NULL != message)
		ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}
