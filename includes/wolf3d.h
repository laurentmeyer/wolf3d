#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"
# include "display.h"
# include "world.h"
# include "input.h"
# include "geometry.h"
# include "timer.h"
# include "assets.h"

# define ERROR -1
# define SUCCESS 0
# define FALSE 0
# define TRUE !FALSE

# define TIMESLICE_US 16666
# define FOV 40

typedef struct		s_ram
{
	t_display		display;
	t_timer			timer;
	t_input			input;
	t_world			world;
	t_assets		assets;
}					t_ram;

int					render_scene(t_ram *ram);
int					init_world(t_ram *ram);
void				print_map(t_ram *ram); //
int					init_hooks(t_ram *ram);
long long			get_time_us(void);


#endif
