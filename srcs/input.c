#include "wolf3d.h"
#include "input.h"
#include "mlx.h"
#include <unistd.h>
#include <math.h>

static int key_press(int keycode, t_ram *ram)
{
	ram->input->keys_pressed[keycode] = 1;
	return (1);
}

static int key_release(int keycode, t_ram *ram)
{
	ram->input->keys_pressed[keycode] = 0;
	return (1);
}

void	 apply_user_input(t_ram *ram)
{
	int			*k;
	t_transform	*player;
	const float	straight_step = 10.0 / 60;
	const float	angle = 90.0 / 60;

	k = ram->input->keys_pressed;
	player = &(ram->world->player);
	if (k[ESC_KEY])
		exit_message(ram, 0, NULL);
	if (k[UP_KEY])
		translate(player, (t_v2){straight_step, 0});
	if (k[DOWN_KEY])
		translate(player, (t_v2){-straight_step, 0});
	if (k[RIGHT_KEY])
		rotate(player, angle);
	if (k[LEFT_KEY])
		rotate(player, -angle);
	// faire varier en fonction de deltatime
}

int init_hooks(t_ram *ram)
{
	mlx_hook(ram->display->win->win_ptr, KEY_PRESS_EVENT, KEY_PRESS_MASK, &key_press, ram);
	mlx_hook(ram->display->win->win_ptr, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, &key_release, ram);
	mlx_loop_hook(ram->display->mlx_ptr, &main_loop, ram);
	return (SUCCESS);
}