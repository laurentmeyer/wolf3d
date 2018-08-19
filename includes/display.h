#ifndef DISPLAY_H
# define DISPLAY_H

# define WIN_H 480
# define WIN_W 640
# define WIN_NAME "wolf3d"

# include "ft_mlx.h"

typedef struct		s_display
{

	void			*mlx_ptr;
	t_window		*map_win;
	t_image			*map_img;
	t_window		*fps_win;
	t_image			*fps_img;
}					t_display;

#endif