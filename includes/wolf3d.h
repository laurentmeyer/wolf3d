#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"

typedef struct		s_ram
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_ram;

#endif
