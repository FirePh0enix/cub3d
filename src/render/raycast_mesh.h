/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_mesh.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:04:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 12:59:56 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_MESH_H
# define RAYCAST_MESH_H

# include "../math/vec.h"
# include "types.h"
# include <stdbool.h>

# define EPSILON 0.000001

typedef struct s_vars
{
	float	a;
	float	f;
	float	t;
	float	u;
	float	v;
}	t_vars;

/*
 Fast Ray/Triangle instersection aglorithm.
 https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
 */
inline bool	intersect_with_triangle(t_ray *ray, t_triangle tri, t_vars vars)
{
	t_v3		edge1;
	t_v3		edge2;
	t_v3		h;
	t_v3		s;
	t_v3		q;

	edge1 = v3_sub(tri.v1, tri.v0);
	edge2 = v3_sub(tri.v2, tri.v0);
	h = v3_cross(ray->dir, edge2);
	vars.a = v3_dot(edge1, h);
	if (vars.a > -EPSILON && vars.a < EPSILON)
		return (false);
	vars.f = 1.0 / vars.a;
	s = v3_sub(ray->origin, tri.v0);
	vars.u = vars.f * v3_dot(s, h);
	if (vars.u < 0.0 || vars.u > 1.0)
		return (false);
	q = v3_cross(s, edge1);
	vars.v = vars.f * v3_dot(ray->dir, q);
	if (vars.v < 0.0 || vars.u + vars.v > 1.0)
		return (false);
	vars.t = vars.f * v3_dot(edge2, q);
	return (vars.t > EPSILON);
}

inline t_color	r3d_raycast_mesh(t_r3d *r3d, t_mesh *mesh, t_consts consts)
{
	size_t	i;

	(void) r3d;
	i = 0;
	while (i < mesh->vertex_count)
	{
		if (intersect_with_triangle(&consts.ray, (t_triangle){mesh->vertices[i],
				mesh->vertices[i + 1], mesh->vertices[i + 2]}, (t_vars){0}))
			return (0xFFFFFFFF);
		i += 3;
	}
	return (0xFF000000);
}

#endif
