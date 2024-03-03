/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_init.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:41:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 18:09:34 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_INIT_H
# define MAT4_INIT_H

# include "mat4.h"
# include "vec.h"
# include <math.h>
# include <string.h>

# define Z_NEAR 0.1
# define Z_FAR 1000.0

inline t_mat4	mat4_identity(void)
{
	t_mat4	mat;

	mat.d[0][0] = 1.0;
	mat.d[1][1] = 1.0;
	mat.d[2][2] = 1.0;
	mat.d[3][3] = 1.0;
	return (mat);
}

inline float	deg2rad(float f)
{
	return (f / 180.0 * M_PI);
}

inline t_mat4	mat4_projection(float fov, int w, int h)
{
	const float	aspect = (float)h / (float)w;
	const float	fov_rad = 1.0 / tan(fov * 0.5 / 180.0 * M_PI);
	t_mat4		m;

	bzero(&m, sizeof(t_mat4));
	m.d[0][0] = aspect * fov_rad;
	m.d[1][1] = fov_rad;
	m.d[2][2] = -(Z_FAR + Z_NEAR) / (Z_FAR - Z_NEAR);
	m.d[2][3] = 1.0;
	m.d[3][2] = (-2 * Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR);
	return (m);
}

inline t_mat4	mat4_x_rot(float angle)
{
	const float	c = cos(angle);
	const float	s = sin(angle);
	t_mat4		m;

	bzero(&m, sizeof(t_mat4));
	m.d[0][0] = 1.0;
	m.d[1][1] = c;
	m.d[1][2] = s;
	m.d[2][1] = -s;
	m.d[2][2] = c;
	m.d[3][3] = 1.0;
	return (m);
}

inline t_mat4	mat4_z_rot(float angle)
{
	const float	c = cos(angle);
	const float	s = sin(angle);
	t_mat4		m;

	bzero(&m, sizeof(t_mat4));
	m.d[0][0] = c;
	m.d[0][1] = s;
	m.d[1][0] = -s;
	m.d[1][1] = c;
	m.d[2][2] = 1.0;
	m.d[3][3] = 1.0;
	return (m);
}

inline t_mat4	mat4_translation(t_v3 pos)
{
	t_mat4	m;

	bzero(&m, sizeof(t_mat4));
	m.d[0][0] = 1.0;
	m.d[1][1] = 1.0;
	m.d[2][2] = 1.0;
	m.d[3][3] = 1.0;
	m.d[3][0] = pos.x;
	m.d[3][1] = pos.y;
	m.d[3][2] = pos.z;
	return (m);
}

inline t_v3	mat4_multiply_v3(t_mat4 m, t_v3 v)
{
	t_v3	r;
	float	w;

	r.x = m.d[0][0] * v.x + m.d[1][0] * v.y + m.d[2][0] * v.z + m.d[3][0];
	r.y = m.d[0][1] * v.x + m.d[1][1] * v.y + m.d[2][1] * v.z + m.d[3][1];
	r.z = m.d[0][2] * v.x + m.d[1][2] * v.y + m.d[2][2] * v.z + m.d[3][2];
	w = m.d[0][3] * v.x + m.d[1][3] * v.y + m.d[2][3] * v.z + m.d[3][3];
	if (w != 0.0)
	{
		r.x /= w;
		r.y /= w;
		r.z /= w;
	}
	return (r);
}

#endif
