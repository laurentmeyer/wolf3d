#include "ft_math.h"
#include <math.h>

float	normalize_degrees(float degrees)
{
	while (degrees < 0.0)
		degrees += 360.0;
	while (degrees > 360.0)
		degrees -= 360.0;
	return (degrees);
}

float	abs_float(float f)
{
	return (f >= 0.0 ? f : -f);
}

double	lerp_double(double a, double b, double p)
{
	return (a + p * (b - a));
}