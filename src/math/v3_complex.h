/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_complex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:23:06 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/22 13:43:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_COMPLEX_H
# define V3_COMPLEX_H

# include "v3.h"
# include <math.h>

inline t_v3	v3_cross(t_v3 a, t_v3 b)
{
	t_v3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

inline float	v3_length(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float	v3_length_squared(t_v3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

inline t_v3	v3_norm(t_v3 v)
{
	const float length = v3_length(v);

	return (v3(v.x / length, v.y / length, v.z / length));
}

inline float	v3_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

#endif
