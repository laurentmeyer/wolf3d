/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:46:07 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:46:57 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"
# include "display.h"
# include "world.h"
# include "input.h"
# include "geometry.h"
# include "transform.h"
# include "timer.h"
# include "assets.h"
# include "input.h"
# include "render.h"
# include "raycast.h"

# define ERROR -1
# define SUCCESS 0
# define FALSE 0
# define TRUE !FALSE

# define TIMESLICE_US 16666
# define H_FOV 40.0
# define MMAP_PXPM 20

typedef struct		s_ram
{
	t_display		*display;
	t_timer			*timer;
	t_input			*input;
	t_world			*world;
	t_assets		*assets;
	t_render		*render;

	char			*file_name;
}					t_ram;

int					main_loop(t_ram *ram);
t_ram				*init_ram(char *file_name);
void				free_ram(t_ram *ram);
void				init_assets(t_ram *ram);
void				free_assets(t_assets *assets);
void				init_display(t_ram *ram);
void				free_display(t_display *display);
void				init_input(t_ram *ram);
void				free_input(t_input *input);
void				init_render(t_ram *ram);
void				free_render(t_render *render);
void				init_timer(t_ram *ram);
void				free_timer(t_timer *timer);
void				init_world(t_ram *ram);
void				free_world(t_world *world);
void				print_map(t_ram *ram);
int					init_hooks(t_ram *ram);
void				apply_user_input(t_ram *ram);
void				pixel_put(t_image *img, int x, int y, unsigned int color);
int					render_scene(t_ram *ram);
t_hit				raycast(t_ram *ram, t_ray ray);
void				trace_line(t_image *img, t_v2i a, t_v2i b, int color);
void				exit_message(t_ram *ram, int exit_code, char *message);
void				fill_map(t_ram *ram, int y, char *line);
void				raycast_straight_col(t_ram *ram);
void				scale_tex(int height, int *dst, int *src);
void				render_each_col(t_ram *ram, t_image *img);

#endif
