/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rot.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:11:36 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/29 20:48:03 by ledelbec         ###   ########.fr       */
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

t_mat4	mat4_rotation(t_v3 angle);

#endif
