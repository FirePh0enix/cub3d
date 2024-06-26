/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_init.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:41:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/16 12:14:40 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_INIT_H
# define MAT4_INIT_H

# include "mat4.h"
# include "vec.h"
# include "libft.h"
# include <math.h>
# include <string.h>
# include "utils.h"

# define Z_NEAR 0.001
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

inline t_mat4	mat4_projection(float fov, int w, int h)
{
	const float	aspect = (float)h / (float)w;
	const float	fov_rad = 1.0 / tan(deg2rad(fov * 0.5));
	t_mat4		m;

	bzero(&m, sizeof(t_mat4));
	m.d[0][0] = aspect * fov_rad;
	m.d[1][1] = fov_rad;
	m.d[2][2] = -(Z_FAR + Z_NEAR) / (Z_FAR - Z_NEAR);
	m.d[2][3] = -1.0;
	m.d[3][2] = (-2 * Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR);
	return (m);
}

/*static t_mat4	mat4_inv(t_mat4 m)
{
	t_mat4	i;

	float A2323 = m.m22 * m.m33 - m.m23 * m.m32 ;
	float A1323 = m.m21 * m.m33 - m.m23 * m.m31 ;
	float A1223 = m.m21 * m.m32 - m.m22 * m.m31 ;
	float A0323 = m.m20 * m.m33 - m.m23 * m.m30 ;
	float A0223 = m.m20 * m.m32 - m.m22 * m.m30 ;
	float A0123 = m.m20 * m.m31 - m.m21 * m.m30 ;
	float A2313 = m.m12 * m.m33 - m.m13 * m.m32 ;
	float A1313 = m.m11 * m.m33 - m.m13 * m.m31 ;
	float A1213 = m.m11 * m.m32 - m.m12 * m.m31 ;
	float A2312 = m.m12 * m.m23 - m.m13 * m.m22 ;
	float A1312 = m.m11 * m.m23 - m.m13 * m.m21 ;
	float A1212 = m.m11 * m.m22 - m.m12 * m.m21 ;
	float A0313 = m.m10 * m.m33 - m.m13 * m.m30 ;
	float A0213 = m.m10 * m.m32 - m.m12 * m.m30 ;
	float A0312 = m.m10 * m.m23 - m.m13 * m.m20 ;
	float A0212 = m.m10 * m.m22 - m.m12 * m.m20 ;
	float A0113 = m.m10 * m.m31 - m.m11 * m.m30 ;
	float A0112 = m.m10 * m.m21 - m.m11 * m.m20 ;

	float det = m.m00 * ( m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223 ) 
		- m.m01 * ( m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223 ) 
		+ m.m02 * ( m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123 ) 
		- m.m03 * ( m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123 ) ;
	det = 1 / det;

	i.m00 = det *   ( m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223 );
	i.m01 = det * - ( m.m01 * A2323 - m.m02 * A1323 + m.m03 * A1223 );
	i.m02 = det *   ( m.m01 * A2313 - m.m02 * A1313 + m.m03 * A1213 );
	i.m03 = det * - ( m.m01 * A2312 - m.m02 * A1312 + m.m03 * A1212 );
	i.m10 = det * - ( m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223 );
	i.m11 = det *   ( m.m00 * A2323 - m.m02 * A0323 + m.m03 * A0223 );
	i.m12 = det * - ( m.m00 * A2313 - m.m02 * A0313 + m.m03 * A0213 );
	i.m13 = det *   ( m.m00 * A2312 - m.m02 * A0312 + m.m03 * A0212 );
	i.m20 = det *   ( m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123 );
	i.m21 = det * - ( m.m00 * A1323 - m.m01 * A0323 + m.m03 * A0123 );
	i.m22 = det *   ( m.m00 * A1313 - m.m01 * A0313 + m.m03 * A0113 );
	i.m23 = det * - ( m.m00 * A1312 - m.m01 * A0312 + m.m03 * A0112 );
	i.m30 = det * - ( m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123 );
	i.m31 = det *   ( m.m00 * A1223 - m.m01 * A0223 + m.m02 * A0123 );
	i.m32 = det * - ( m.m00 * A1213 - m.m01 * A0213 + m.m02 * A0113 );
	i.m33 = det *   ( m.m00 * A1212 - m.m01 * A0212 + m.m02 * A0112 );

	return i;
}*/

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

// Commenting this code fix the projection problem in r3d_fill_triangle
// r.z /= w;
inline t_v3	mat4_multiply_v3(t_mat4 m, t_v3 v)
{
	t_v3	r;
	float	w;

	r.x = m.d[0][0] * v.x + m.d[1][0] * v.y + m.d[2][0] * v.z + m.d[3][0];
	r.y = m.d[0][1] * v.x + m.d[1][1] * v.y + m.d[2][1] * v.z + m.d[3][1];
	r.z = m.d[0][2] * v.x + m.d[1][2] * v.y + m.d[2][2] * v.z + m.d[3][2];
	w = m.d[0][3] * v.x + m.d[1][3] * v.y + m.d[2][3] * v.z + m.d[3][3];
	if (w != 1.0)
	{
		r.x /= w;
		r.y /= w;
	}
	return (r);
}

#endif
