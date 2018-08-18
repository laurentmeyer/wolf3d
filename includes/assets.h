#ifndef ASSETS_H
# define ASSETS_H

# include "wolf3d.h"
# include "geometry.h"
# include <math.h>

# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TEX_FILENAME "assets/textures.xpm"
# define TEX_FILE_TEX_PER_LINE 6
# define TEX_FILEWIDTH 384
# define TEX_COUNT 110

enum			e_textures
{
	T_STONE = 0,
	T_WALL = 14,
	T_DOOR = 98
};

typedef int		*t_texture;

typedef struct	s_assets
{
	t_texture	*textures;
	// void		*tex_img;
	// char		*tex_addr;
	// int			bpp;
	// int			size_line;
	// int			endian;
}				t_assets;

#endif