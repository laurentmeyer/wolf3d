#ifndef DISPLAY_H
# define DISPLAY_H

# define WIN_H 480
# define WIN_W 640
# define WIN_NAME "wolf3d"

typedef struct		s_image
{
	void			*img_ptr;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				chars_per_pixel;
	int				pixels_per_line;
	int				w;
	int				h;
}					t_image;

typedef struct		s_window
{
	void			*win_ptr;
	int				w;
	int				h;
	char			*name;
}					t_window;

typedef struct		s_display
{

	void			*mlx_ptr;
	t_window		*win;
	t_image			*img;
}					t_display;

#endif