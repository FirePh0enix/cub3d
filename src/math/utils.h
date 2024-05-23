#ifndef UTILS_H
# define UTILS_H

# include <math.h>

inline float	max3f(float a, float b, float c)
{
	return (fmaxf(a, fmaxf(b, c)));
}

inline float	min3f(float a, float b, float c)
{
	return (fminf(a, fminf(b, c)));
}

inline float	clampf(float f, float min, float max)
{
	return (fmaxf(min, fminf(f, max)));
}

#endif
