/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:26:39 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/01 00:38:57 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdbool.h>
#include <math.h>

/*
 Fast Ray/Triangle instersection aglorithm.
 https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
 */
static bool	intersect_with_triangle(t_ray *ray, t_triangle triangle)
{
	const float	EPSILON = 0.000001;
	t_v3		edge1, edge2, h, s, q;
	float		a, f;
	float		t, u, v;
	
	edge1 = v3_sub(triangle.v1, triangle.v0);
	edge2 = v3_sub(triangle.v2, triangle.v0);

	h = v3_cross(ray->dir, edge2);
	a = v3_dot(edge1, h);

	if (a > -EPSILON && a < EPSILON)
		return false;

	f = 1.0 / a;
	s = v3_sub(ray->origin, triangle.v0);

	u = f * v3_dot(s, h);
	if (u < 0.0 || u > 1.0)
		return false;

	q = v3_cross(s, edge1);
	v = f * v3_dot(ray->dir, q);
	if (v < 0.0 || u + v > 1.0)
		return false;

	t = f * v3_dot(edge2, q);
	if (t > EPSILON)
		return true;
	else
		return false;
}

void	r3d_raycast_triangle(t_r3d *r3d, t_triangle triangle)
{
	float	fov = 51.52;
	float	scale = tan((fov * 0.5) * 3.1415926535 / 180.0);
	float	aspect_ratio = (float)r3d->width / (float)r3d->height;
	int		x;
	int		y;

	y = 0;
	while (y < r3d->height)
	{
		x = 0;
		while (x < r3d->width)
		{
			float	rx = (2.0 * ((x + 0.5) / (float)r3d->width) - 1) * aspect_ratio * scale;
			float	ry = (1 - 2.0 * ((y + 0.5) / (float)r3d->height)) * scale;
			t_ray	ray = {{0.0, 0.0, 0.0}, v3_norm((t_v3){rx, ry, -1})};

			if (intersect_with_triangle(&ray, triangle))
				((unsigned int *)r3d->buffer->data)[x + y * r3d->width] = 0xFFFFFFFF;
			x++;
		}
		y++;
	}
}
