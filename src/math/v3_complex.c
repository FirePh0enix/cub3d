/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:23:34 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/01 00:50:07 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

static float	q_rsqrt(float number)
{
	int		i; // int -> float : long was 32-bits during Quake III era
	float	x2;
	float	y;

	x2 = number * 0.5F;
	y = number;
	i = *(int *) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *) &i;
	y = y * (1.5F - (x2 * y * y));
	return (y);
}

t_v3	v3_cross(t_v3 a, t_v3 b)
{
	t_v3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

float	v3_length(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_v3	v3_norm(t_v3 v)
{
	//const float	length = v3_length(v);
	const float	inv_length = q_rsqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	return ((t_v3){v.x / inv_length, v.y / inv_length, v.z / inv_length});
}

float	v3_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
