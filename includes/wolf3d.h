#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"
# include "display.h"

# define ERROR -1
# define SUCCESS 0
# define FALSE 0
# define TRUE !FALSE

# define SIMULATION_DT 4
# define DISPLAY_DT 16

typedef struct		s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_state
{
	void			*s;
}					t_state;

typedef struct		s_ram
{
	t_display		display;
	t_state			state;
}					t_ram;

int	g_verbose; //


int		get_time_ms(void);
int 	init_hooks(t_ram *ram);

#endif
