/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:43:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/20 11:01:14 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "shader.h"

/*
 * Reference:
 * http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html#algo1
 * https://www.youtube.com/watch?v=k5wtuKWmV48
 */

static inline float	max3f(float a, float b, float c)
{
	return (fmaxf(a, fmaxf(b, c)));
}

static inline float	min3f(float a, float b, float c)
{
	return (fminf(a, fminf(b, c)));
}

inline float	edge_fn(t_v3 a, t_v3 b, t_v3 c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
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
	return ((t_v3){{
		(w.x * v0.x + w.y * v1.x + w.z * v2.x) * z,
		(w.x * v0.y + w.y * v1.y + w.z * v2.y) * z,
		(w.x * v0.z + w.y * v1.z + w.z * v2.z) * z
	}});
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

inline float	clamp(int f, int min, int max)
{
	return (fmaxf(min, fminf(f, max)));
}

void	r3d_fill_triangle(
		t_r3d *r3d, t_tri tri, t_mtl *mtl,
		t_color *cbuf, float *dbuf)
{
	t_v3	tmp;
	t_v2	tmp2;

	// TODO: edge_fn should be modified to work with clockwise triangles.
	tmp = tri.v2;
	tri.v2 = tri.v1;
	tri.v1 = tmp;
	tmp2 = tri.t2;
	tri.t2 = tri.t1;
	tri.t1 = tmp2;

	tri.v0 = mat4_multiply_v3(r3d->projection_matrix, tri.v0);
	tri.v1 = mat4_multiply_v3(r3d->projection_matrix, tri.v1);
	tri.v2 = mat4_multiply_v3(r3d->projection_matrix, tri.v2);

	// Convert from screen space to NDC then raster (in one go)
	tri.v0.x = (1 + tri.v0.x) * 0.5 * r3d->width, tri.v0.y = (1 + tri.v0.y) * 0.5 * r3d->height;
	tri.v1.x = (1 + tri.v1.x) * 0.5 * r3d->width, tri.v1.y = (1 + tri.v1.y) * 0.5 * r3d->height;
	tri.v2.x = (1 + tri.v2.x) * 0.5 * r3d->width, tri.v2.y = (1 + tri.v2.y) * 0.5 * r3d->height;

	int	min_x, max_x, min_y, max_y;

	min_x = min3f(tri.v0.x, tri.v1.x, tri.v2.x);
	max_x = max3f(tri.v0.x, tri.v1.x, tri.v2.x);
	min_y = min3f(tri.v0.y, tri.v1.y, tri.v2.y);
	max_y = max3f(tri.v0.y, tri.v1.y, tri.v2.y);

	// The triangle is outside of the screen.
	// TODO This check could probably be sooner. (maybe before NDC to screen space)
	if (min_x >= r3d->width || min_y >= r3d->height)
		return ;

	min_x = fmaxf(min_x, 0);
	min_y = fmaxf(min_y, 0);
	max_x = fminf(max_x, r3d->width - 1);
	max_y = fminf(max_y, r3d->height - 1);

	pint_v2(&tri.t0, &tri.t1, &tri.t2, &tri);
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

				float z = (w0 * tri.v0.z + w1 * tri.v1.z + w2 * tri.v2.z);
				float one_z = 1 / z	;
				t_v3	w = {{w0, w1, w2}};
				t_v2	uv = int_v2(tri.t0, tri.t1, tri.t2, w, one_z);

				if (z < dbuf[j * r3d->width + i])
					continue ;
				dbuf[j * r3d->width + i] = z;
				cbuf[j * r3d->width + i] = shader(r3d, mtl, z, uv);
			}
		}
	}
}
