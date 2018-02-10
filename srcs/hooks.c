#include "wolf3d.h"
#include "input.h"
#include "mlx.h"
#include <unistd.h>
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

void	translate(t_vector2 *pos, t_vector2 direction)
{
	pos->x += direction.x;
	pos->y += direction.y;
} 

int apply_user_input(t_ram *ram)
{
	// int	i;
	int	*k;

	k = ram->input.keys_pressed;
	if (k[ESC_KEY])
		exit(0);
	if (k[UP_KEY])
		translate(&(ram->world.player_pos), (t_vector2){0, -1});
	if (k[DOWN_KEY])
		translate(&(ram->world.player_pos), (t_vector2){0, 1});
	if (k[RIGHT_KEY])
		translate(&(ram->world.player_pos), (t_vector2){1, 0});
	if (k[LEFT_KEY])
		translate(&(ram->world.player_pos), (t_vector2){-1, 0});
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