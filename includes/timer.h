#ifndef TIMER_H
# define TIMER_H

typedef struct	s_timer
{
	int			delta_time_us;
}				t_timer;

long long		get_time_us(void);

#endif