#include <sys/time.h>
#include "wolf3d.h"
#include <stdio.h> //
#include "ft_printf.h" //

long long	get_time_us(void)
{
    static struct timespec	start;
    struct timespec			now;
    static int              only_once = 1;
    long long				diff;

    if (only_once)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        only_once = 0;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    diff = (now.tv_sec - start.tv_sec) * 1000000;
	diff += (now.tv_nsec - start.tv_nsec) / 1000;
    return (diff);
}