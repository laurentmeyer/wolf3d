#include "wolf3d.h"
#include "hooks.h"
#include <unistd.h>
#include "ft_printf.h"//j

static int key_hooks(int keycode, t_ram *ram)
{
    if (NULL != ram && keycode == ESC_KEY)
        exit(0);
    return (1);
}

int     update_world(t_world *world, int dt)
{
	(void)world;
	dt++;
    return (SUCCESS);
}

static int main_loop(t_ram *ram)
{
    long long 			real_time;
    static long long	simulation_time = 0;

    real_time = get_time_us();
    while (simulation_time < real_time)
    {
        update_world(&(ram->world), TIMESLICE_US);
        simulation_time += TIMESLICE_US;
    }
    render_scene(ram);
    return (1);
}

int init_hooks(t_ram *ram)
{
    mlx_key_hook(ram->display.window, &key_hooks, ram);
    mlx_loop_hook(ram->display.mlx_ptr, &main_loop, ram);
    return (1);
}