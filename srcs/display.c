/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 17:34:55 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/29 17:35:19 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "display.h"

void	pixel_put(t_image *img, int x, int y, unsigned int color)
{
	ft_memcpy(img->data_addr + (img->pixels_per_line * y + x) *
			img->chars_per_pixel, (const void *)(&color), img->chars_per_pixel);
}
