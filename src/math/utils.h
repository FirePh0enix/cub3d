#ifndef UTILS_H
# define UTILS_H

# include <math.h>

inline float_t	max2(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

inline float_t	min2(float x, float y)
{
	if (x < y)
		return (x);
	return (y);
}

inline float	max3f(float a, float b, float c)
{
	return (max2(a, max2(b, c)));
}

inline float	min3f(float a, float b, float c)
{
	return (min2(a, min2(b, c)));
}

inline float	clampf(float f, float min, float max)
{
	return (max2(min, min2(f, max)));
}

inline float	lerpf(float a, float b, float t)
{
	return (a + t * (b - a));
}

#endif
