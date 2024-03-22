/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:40:34 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/22 11:54:13 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

typedef union s_mat4
{
	float		d[4][4];
	struct
	{
		float	m00;
		float	m01;
		float	m02;
		float	m03;
		float	m10;
		float	m11;
		float	m12;
		float	m13;
		float	m20;
		float	m21;
		float	m22;
		float	m23;
		float	m30;
		float	m31;
		float	m32;
		float	m33;
	};
}	t_mat4;

#endif
