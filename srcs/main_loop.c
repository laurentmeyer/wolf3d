#include "wolf3d.h"

int update_world(t_ram *ram)
{
	apply_user_input(ram);
	return (SUCCESS);
}

int						main_loop(t_ram *ram)
{
	long long 			real_time;
	static long long	simulation_time = 0;

	real_time = get_time_us();
	while (simulation_time < real_time)
	{
		update_world(ram);
		simulation_time += ram->timer->delta_time_us;
	}
	render_scene(ram);
	return (SUCCESS);
}