/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 15:36:14 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer.h"
#include "shader.h"
#include <stdio.h>

/*
 * Reference:
 * http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html#algo1
 * https://www.youtube.com/watch?v=k5wtuKWmV48
 */

inline float	edge_fn(t_v3 a, t_v3 b, t_v3 c)
{
	return ((a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x));
}

/*
 * Two steps are necessary to correctly interpolate a value:
 * - Divide every values by their associated z vertex component.
 * - Compute the interpolate value.
 */

inline void	pint_v3(t_v3 *v0, t_v3 *v1, t_v3 *v2, t_tri *tri)
{
	v0->x /= tri->v0.z;
	v0->y /= tri->v0.z;
	v1->x /= tri->v1.z;
	v1->y /= tri->v1.z;
	v2->x /= tri->v2.z;
	v2->y /= tri->v2.z;
}

inline t_v3	int_v3(t_v3 v0, t_v3 v1, t_v3 v2, t_v3 w, float z)
{
	return (v3(
		(w.x * v0.x + w.y * v1.x + w.z * v2.x) * z,
		(w.x * v0.y + w.y * v1.y + w.z * v2.y) * z,
		(w.x * v0.z + w.y * v1.z + w.z * v2.z) * z
	));
}

inline void	pint_v2(t_v2 *v0, t_v2 *v1, t_v2 *v2, t_tri *tri)
{
	v0->x /= tri->v0.z;
	v0->y /= tri->v0.z;
	v1->x /= tri->v1.z;
	v1->y /= tri->v1.z;
	v2->x /= tri->v2.z;
	v2->y /= tri->v2.z;
}

inline t_v2	int_v2(t_v2 v0, t_v2 v1, t_v2 v2, t_v3 w, float z)
{
	return ((t_v2){
		(w.x * v0.x + w.y * v1.x + w.z * v2.x) * z,
		(w.x * v0.y + w.y * v1.y + w.z * v2.y) * z,
	});
}

inline void	pint_v1(float *v0, float *v1, float *v2, t_tri *tri)
{
	*v0 /= tri->v0.z;
	*v1 /= tri->v1.z;
	*v2 /= tri->v2.z;
}

inline float	int_v1(float v0, float v1, float v2, t_v3 w, float z)
{
	return ((w.x * v0 + w.y * v1 + w.z * v2) * z);
}

void	rasterize_triangle(t_rasterizer *rast, t_tri tri, t_color col)
{
	const t_v2i	size = rasterizer_get_size(rast);

	tri.v0 = mat4_multiply_v3(rast->projection_matrix, tri.v0);
	tri.v1 = mat4_multiply_v3(rast->projection_matrix, tri.v1);
	tri.v2 = mat4_multiply_v3(rast->projection_matrix, tri.v2);

	// NOTE:
	// This fix the depth buffer bug. There is still a performance hit when the camera enters a mesh.
	// if (tri.v0.z < 0.1 || tri.v1.z < 0.1 || tri.v2.z < 0.1)
	// {
	// 	return ;
	// }

	// Convert from screen space to NDC then raster (in one go)
	tri.v0.x = (1 + tri.v0.x) * 0.5 * size.x, tri.v0.y = (1 + tri.v0.y) * 0.5 * size.y;
	tri.v1.x = (1 + tri.v1.x) * 0.5 * size.x, tri.v1.y = (1 + tri.v1.y) * 0.5 * size.y;
	tri.v2.x = (1 + tri.v2.x) * 0.5 * size.x, tri.v2.y = (1 + tri.v2.y) * 0.5 * size.y;

	int	min_x, max_x, min_y, max_y;

	min_x = min3f(tri.v0.x, tri.v1.x, tri.v2.x);
	max_x = max3f(tri.v0.x, tri.v1.x, tri.v2.x);
	min_y = min3f(tri.v0.y, tri.v1.y, tri.v2.y);
	max_y = max3f(tri.v0.y, tri.v1.y, tri.v2.y);

	// The triangle is outside of the screen.
	// TODO This check could probably be sooner. (maybe before NDC to screen space)
	if (min_x >= size.x || min_y >= size.y || max_x < 0 || max_y < 0)
		return ;

	min_x = fmaxf(min_x, 0);
	min_y = fmaxf(min_y, 0);
	max_x = fminf(max_x, size.x - 1);
	max_y = fminf(max_y, size.y - 1);

	pint_v2(&tri.t0, &tri.t1, &tri.t2, &tri);
	pint_v3(&tri.n0, &tri.n1, &tri.n2, &tri);
	tri.v0.z = 1 / tri.v0.z, tri.v1.z = 1 / tri.v1.z, tri.v2.z = 1 / tri.v2.z;

	float area = edge_fn(tri.v0, tri.v1, tri.v2);

	for (int j = min_y; j <= max_y; ++j)
	{
		for (int i = min_x; i <= max_x; ++i)
		{
			t_v3 p = {{i + 0.5f, j + 0.5f, 0.0}};
			float w0 = edge_fn(tri.v1, tri.v2, p);
			float w1 = edge_fn(tri.v2, tri.v0, p);
			float w2 = edge_fn(tri.v0, tri.v1, p);
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area, w1 /= area, w2 /= area;

				float	z = (w0 * tri.v0.z + w1 * tri.v1.z + w2 * tri.v2.z);
				float	one_z = 1 / z;
				t_v3	w = v3(w0, w1, w2);
				t_v2	uv = int_v2(tri.t0, tri.t1, tri.t2, w, one_z);
				// t_v3	n = int_v3(tri.n0, tri.n1, tri.n2, w, one_z);

				size_t	index = i + (size.y - j - 1) * size.x;
				size_t	index2;
				if (rast->flip)
					index2 = rast->rect.min.x + i + (rast->r3d->height - (rast->rect.min.y + j) - 1) * rast->r3d->width;
				else
					index2 = rast->rect.min.x + i + (rast->rect.min.y + j) * rast->r3d->width;

				// FIXME: When camera is near the mesh, fps drops
				if (z < rast->depth_buffer[index] || z < 0.0 || z > 1.0)
					continue ;

				rast->depth_buffer[index] = z;
				rast->r3d->color_buffer[index2] = shader(rast->r3d, uv, col);
			}
		}
	}
}
