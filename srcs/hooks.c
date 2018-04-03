#include "wolf3d.h"
#include "input.h"
#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include "ft_printf.h"//j

static int key_press(int keycode, t_ram *ram)
{
	ram->input.keys_pressed[keycode] = 1;
	return (1);
}

static int key_release(int keycode, t_ram *ram)
{
	ram->input.keys_pressed[keycode] = 0;
	return (1);
}

void	translate(t_player *player, t_v2 v)
{
	// je ne mets pas de gestion de sortie car les maps sont censées être protégées par des murs
	t_v2	move;
	float		angle;

	angle = player->angle * PI / 180.0;
	move.x = v.x * cos(angle) - v.y * sin(angle);
	move.y = v.x * sin(angle) + v.y * cos(angle);
	player->pos.x += move.x;
	player->pos.y += move.y;
} 

void	rotate(t_player *player, float angle)
{
	player->angle += angle;
} 

int apply_user_input(t_ram *ram)
{
	int			*k;
	t_player	*player;
	const float	straight_step = 30.0 / 60;
	const float	angle = 30.0 / 60;

	k = ram->input.keys_pressed;
	player = &(ram->world.player);
	if (k[ESC_KEY])
		exit(0); // gérer mieux
	if (k[UP_KEY])
		translate(player, (t_v2){straight_step, 0});
	if (k[DOWN_KEY])
		translate(player, (t_v2){-straight_step, 0});
	if (k[RIGHT_KEY])
		rotate(player, -angle);
	if (k[LEFT_KEY])
		rotate(player, angle);
	// faire varier en fonction de deltatime
	return (SUCCESS);
}

int update_world(t_ram *ram)
{
	apply_user_input(ram);
	return (SUCCESS);
}

static int main_loop(t_ram *ram)
{
	long long real_time;
	static long long simulation_time = 0;

	real_time = get_time_us();
	while (simulation_time < real_time)
	{
		update_world(ram);
		simulation_time += ram->timer.delta_time_us;
	}
	render_scene(ram);
	return (SUCCESS);
}

int init_hooks(t_ram *ram)
{
	mlx_hook(ram->display.window, KEY_PRESS_EVENT, KEY_PRESS_MASK, &key_press, ram);
	mlx_hook(ram->display.window, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, &key_release, ram);
	mlx_loop_hook(ram->display.mlx_ptr, &main_loop, ram);
	return (SUCCESS);
}