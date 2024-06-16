/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rot.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:11:36 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/16 12:14:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_ROT_H
# define MAT4_ROT_H

# include "mat4.h"
# include "mat4_mul.h"
# include "v3.h"
# include "libft.h"
# include <math.h>

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

#endif
