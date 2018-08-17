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
	t_display		*display;
	t_timer			*timer;
	t_input			*input;
	t_world			*world;
	t_assets		*assets;
}					t_ram;

t_ram				*init_ram(void);
void				free_ram(t_ram *ram);
void				init_assets(t_ram *ram);
void				free_assets(t_assets *assets);
void				init_display(t_ram *ram);
void				free_display(t_display *display);
void				init_input(t_ram *ram);
void				free_input(t_input *input);
void				init_timer(t_ram *ram);
void				free_timer(t_timer *timer);
void				init_world(t_ram *ram);
void				free_world(t_world *world);
void				print_map(t_ram *ram); //
int					init_hooks(t_ram *ram);
int					render_scene(t_ram *ram);
void				exit_message(t_ram *ram, int exit_code, char *message);


#endif
