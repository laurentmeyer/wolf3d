#include <sys/time.h>
#include "wolf3d.h"
#include <stdio.h> //
#include "ft_printf.h" //

long long	get_time_us(void)
{
    struct timespec			now;
    long long				diff;

    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    diff = now.tv_sec * 1000000;
	diff += now.tv_nsec / 1000;
    return (diff);
}