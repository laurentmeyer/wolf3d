#ifndef DISPLAY_H
# define DISPLAY_H

typedef	struct		s_framebuf
{
	void			*img_ptr;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				chars_per_pixel;
	int				pixels_per_line;
}					t_framebuf;

typedef void		*t_window;

typedef struct		s_display
{

	void			*mlx_ptr;
	t_window		window;
	int				win_width;
	int				win_height;
	t_framebuf		framebuf;
}					t_display;

#endif