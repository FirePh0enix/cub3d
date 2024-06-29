/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:47:40 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/29 20:47:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4_rot.h"

t_mat4	mat4_rotation(t_v3 angle)
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
