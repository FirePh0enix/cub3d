/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:26:39 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 00:18:54 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdbool.h>

inline t_v3	inlined_sub(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x - b.x, a.y - b.y, a.z - b.z});
}

inline t_v3	inlined_cross(t_v3 a, t_v3 b)
{
	t_v3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

inline float	inlined_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
 Fast Ray/Triangle instersection aglorithm.
 https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
 */
static bool	intersect_with_triangle(t_ray *ray, t_v3 v0, t_v3 v1, t_v3 v2)
{
	const float	EPSILON = 0.000001;
	t_v3		edge1, edge2, h, s, q;
	float		a, f;
	float		t, u, v;
	
	edge1 = inlined_sub(v1, v0);
	edge2 = inlined_sub(v2, v0);
	h = inlined_cross(ray->dir, edge2);
	a = inlined_dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return false;
	f = 1.0 / a;
	s = inlined_sub(ray->origin, v0);
	u = f * inlined_dot(s, h);
	if (u < 0.0 || u > 1.0)
		return false;
	q = inlined_cross(s, edge1);
	v = f * inlined_dot(ray->dir, q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	t = f * inlined_dot(edge2, q); // PERF: ~0.8ms total
	return (t > EPSILON);
}

t_color	r3d_raycast_mesh(t_r3d *r3d, t_mesh *mesh, t_consts consts)
{
	size_t	i;

	(void) r3d;
	i = 0;
	while (i < mesh->vertex_count)
	{
		if (intersect_with_triangle(&consts.ray, mesh->vertices[i],
				mesh->vertices[i + 1], mesh->vertices[i + 2]))
			return (0xFFFFFFFF);
		i += 3;
	}
	return (0xFF000000);
}
