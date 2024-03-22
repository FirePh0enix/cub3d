/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_init.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:41:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/22 12:24:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_INIT_H
# define MAT4_INIT_H

# include "mat4.h"
# include "vec.h"
# include "libft.h"
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
	const float	fov_rad = 1.0 / tan(deg2rad(fov * 0.5));
	t_mat4		m;

	bzero(&m, sizeof(t_mat4));
	m.d[0][0] = aspect * fov_rad;
	m.d[1][1] = fov_rad;
	m.d[2][2] = (-Z_FAR + Z_NEAR) / (Z_FAR - Z_NEAR);
	m.d[2][3] = -1.0;
	m.d[3][2] = (-2 * Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR);
	return (m);
}

inline t_mat4	mat4_mul_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4	m;

	m.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
	m.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
	m.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
	m.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
	m.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
	m.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
	m.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
	m.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
	m.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
	m.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
	m.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
	m.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
	m.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
	m.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
	m.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
	m.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;
	return (m);
}

inline t_mat4	_mat4_rotx_int(float c, float s)
{
	t_mat4	m;

	ft_bzero(&m, sizeof(t_mat4));
	m.d[0][0] = 1.0;
	m.d[1][1] = c;
	m.d[1][2] = s;
	m.d[2][1] = -s;
	m.d[2][2] = c;
	m.d[3][3] = 1.0;
	return (m);
}

inline t_mat4	_mat4_roty_int(float c, float s)
{
	t_mat4	m;

	ft_bzero(&m, sizeof(t_mat4));
	m.d[0][0] = c;
	m.d[0][2] = -s;
	m.d[1][1] = 1.0;
	m.d[2][0] = s;
	m.d[2][2] = c;
	m.d[3][3] = 1.0;
	return (m);
}

inline t_mat4	_mat4_rotz_int(float c, float s)
{
	t_mat4	m;

	ft_bzero(&m, sizeof(t_mat4));
	m.d[0][0] = c;
	m.d[0][1] = s;
	m.d[1][0] = -s;
	m.d[1][1] = c;
	m.d[2][2] = 1.0;
	m.d[3][3] = 1.0;
	return (m);
}

// FIXME Put in a separate file
static t_mat4	mat4_rotation(t_v3 angle)
{
	const t_v3	c = v3(cos(angle.x), cos(angle.y), cos(angle.z));
	const t_v3	s = v3(sin(angle.x), sin(angle.y), sin(angle.z));
	t_mat4		rotx;
	t_mat4		roty;
	t_mat4		rotz;

	rotx = _mat4_rotx_int(c.x, s.x);
	roty = _mat4_roty_int(c.y, s.y);
	rotz = _mat4_rotz_int(c.z, s.z);
	return (mat4_mul_mat4(rotx, mat4_mul_mat4(roty, rotz)));
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
		// Commenting this code fix the projection problem in r3d_fill_triangle
		// r.z /= w;
	}
	return (r);
}

#endif
