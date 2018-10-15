/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:45:24 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:46:02 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "wolf3d.h"
# include "transform.h"
# include "geometry.h"

# define GROUND_COLOR 0x383838
# define SKY_COLOR 0xff0000

# define TEX_EMPTY -2
# define TEX_WALL_STONE 0
# define TEX_WALL_STONE_2 2
# define TEX_FLAG_NAZI 4
# define TEX_HITLER_STONE 6
# define TEX_PRISON_EMPTY 8
# define TEX_PRISON_DEAD 12
# define TEX_WALL_BLUE 14
# define TEX_WALL_BLUE_2 16
# define TEX_NAZI_CUP 18
# define TEX_HITLER_WOOD 20
# define TEX_WALL_WOOD 22
# define TEX_METAL_DOOR 24
# define TEX_VERBOTEN_DOOR 26
# define TEX_BLUE_METAL_DOOR 28
# define TEX_RED_STONE_WALL 32
# define TEX_RED_STONE_NAZI_WALL 34
# define TEX_FUHRER_PORTRAIT 95

# define TEX_ITEM 0

typedef struct		s_world
{
	char			*map;
	int				map_w;
	int				map_h;
	t_transform		player;
}					t_world;

#endif
