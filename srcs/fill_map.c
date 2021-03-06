/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 19:22:18 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 13:59:06 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	get_texture_aux(char *line, int x)
{
	char	c;

	if ('B' == line[x])
		c = TEX_WALL_BLUE;
	else if ('S' == line[x])
		c = TEX_HITLER_STONE;
	else if ('F' == line[x])
		c = TEX_FLAG_NAZI;
	else if ('P' == line[x])
		c = TEX_PRISON_EMPTY;
	else if ('D' == line[x])
		c = TEX_PRISON_DEAD;
	else if ('T' == line[x])
		c = TEX_RED_STONE_WALL;
	else if ('R' == line[x])
		c = TEX_WALL_STONE;
	else if ('U' == line[x])
		c = TEX_FUHRER_PORTRAIT;
	else if ('W' == line[x])
		c = TEX_WALL_WOOD;
	else if ('I' == line[x])
		c = TEX_ITEM;
	else
		c = TEX_EMPTY;
	return (c);
}

static char	get_texture(t_ram *ram, char *line, int x, int y)
{
	char	c;

	c = get_texture_aux(line, x);
	if (TEX_EMPTY == c && (0 == x || ram->world->map_w - 1 == x || 0 == y
		|| ram->world->map_h - 1 == y))
		c = TEX_WALL_STONE;
	return (c);
}

void		fill_map(t_ram *ram, int y, char *line)
{
	int		x;

	x = 0;
	while (x < ram->world->map_w && '\0' != line[x])
	{
		ram->world->map[x + ram->world->map_w * y] =
			get_texture(ram, line, x, y);
		++x;
	}
	while (x < ram->world->map_w)
		ram->world->map[x++ + ram->world->map_w * y] = TEX_WALL_STONE;
}
