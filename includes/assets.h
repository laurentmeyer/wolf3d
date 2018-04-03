#ifndef ASSETS_H
# define ASSETS_H

# include "geometry.h"

typedef struct	s_texture
{
	void		*lit;
	void		*unlit;
	int			width;
	int			length;
}				t_texture;

typedef struct	s_textures
{
	t_texture	wall;
}				t_textures;

typedef struct	s_assets
{
	float		sintable[ANGLES + ANGLES / 4];
	float		*costable;
	t_textures	textures;
}				t_assets;

#endif