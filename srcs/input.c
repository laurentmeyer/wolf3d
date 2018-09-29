#include "wolf3d.h"
#include "input.h"
#include "mlx.h"
#include "ft_math.h"
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

// t_v2	legal_move(t_ram *ram, t_v2 move)
// {
// 	t_transform	dst;
// 	t_v2i		player;
// 	const float	epsilon = 0.1;

// 	dst = translate(ram->world->player, (t_v2){move.x + epsilon, move.y});
// 	if (TEX_EMPTY == (ram->world->map)[(int)(dst.pos.y) * ram->world->map_w + (int)(dst.pos.x)])
// 		return (translate(ram->world->player, move).pos);
// 	dst = translate(ram->world->player, move);
// 	player = (t_v2i){(int)(ram->world->player.pos.x), (int)(ram->world->player.pos.y)};
// 	if ((int)(dst.pos.x) != (int)(player.x))
// 		dst.pos.x = ((int)(dst.pos.x) > player.x) ? (int)(dst.pos.x) : player.x;
// 	if (dst.pos.y != player.y)
// 		dst.pos.y = ((int)(dst.pos.y) > player.y) ? (int)(dst.pos.y) : player.y;
// 	if (dst.pos.x - (int)(dst.pos.x) < epsilon)
// 		dst.pos.x = (int)(dst.pos.x) + epsilon;
// 	if ((int)(dst.pos.x) + 1.0 - dst.pos.x < epsilon)
// 		dst.pos.x = (int)(dst.pos.x) + 1.0 - epsilon;
// 	if (dst.pos.y - (int)(dst.pos.y) < epsilon)
// 		dst.pos.y = (int)(dst.pos.y) + epsilon;
// 	if ((int)(dst.pos.y) + 1.0 - dst.pos.y < epsilon)
// 		dst.pos.y = (int)(dst.pos.y) + 1.0 - epsilon;
// 	return (dst.pos);
// }

char	get_tex(t_ram *ram, float x, float y)
{
	return ((ram->world->map)[(int)y * ram->world->map_w + (int)x]);
}

t_v2	legal_move(t_ram *ram, t_v2 move)
{
	t_transform	dst;
	// t_v2i		hit;
	t_v2		res;
	// const float	epsilon = 0.1;

	res = ram->world->player.pos;
	dst = translate(ram->world->player, move);
	if (TEX_EMPTY == get_tex(ram, dst.pos.x, res.y))
		res.x = dst.pos.x;
	if (TEX_EMPTY == get_tex(ram, ram->world->player.pos.x, dst.pos.y)
		&& TEX_EMPTY == get_tex(ram, res.x, dst.pos.y))
		res.y = dst.pos.y;
	return (res);
}

// t_v2 legal_move(t_ram *ram, t_v2 move)
// {
// 	t_transform origin;

// 	origin = translate(ram->world->player, move);
// 	if (TEX_EMPTY == (ram->world->map)[(int)(origin.pos.y) * ram->world->map_w + (int)(origin.pos.x)])
// 		return (origin.pos);
// 	return (ram->world->player.pos);
// }

void	 apply_user_input(t_ram *ram)
{
	int			*k;
	t_transform	*player;
	const float	straight_step = 3.0 / 60;
	const float	angle = 90.0 / 60;

	k = ram->input->keys_pressed;
	player = &(ram->world->player);
	if (k[ESC_KEY])
		exit_message(ram, 0, NULL);
	if (k[UP_KEY])
		player->pos = legal_move(ram, (t_v2){straight_step, 0});
	if (k[DOWN_KEY])
		player->pos = legal_move(ram, (t_v2){-straight_step, 0});
	if (k[RIGHT_KEY])
		rotate(player, -angle);
	if (k[LEFT_KEY])
		rotate(player, angle);
}

int init_hooks(t_ram *ram)
{
	mlx_hook(ram->display->map_win->win_ptr, KEY_PRESS_EVENT, KEY_PRESS_MASK, &key_press, ram);
	mlx_hook(ram->display->map_win->win_ptr, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, &key_release, ram);
	mlx_hook(ram->display->fps_win->win_ptr, KEY_PRESS_EVENT, KEY_PRESS_MASK, &key_press, ram);
	mlx_hook(ram->display->fps_win->win_ptr, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, &key_release, ram);
	mlx_loop_hook(ram->display->mlx_ptr, &main_loop, ram);
	return (SUCCESS);
}