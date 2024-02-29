/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:06:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/28 22:53:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

t_v3	v3_add(t_v3 a, t_v3 b);
t_v3	v3_sub(t_v3 a, t_v3 b);
t_v3	v3_scale(t_v3 v, float scale);

float	v3_length(t_v3 v);
t_v3	v3_norm(t_v3 v);
t_v3	v3_cross(t_v3 a, t_v3 b);
float	v3_dot(t_v3 a, t_v3 b);

t_v3	triangle_normal(t_v3 v0, t_v3 v1, t_v3 v2);

#endif
