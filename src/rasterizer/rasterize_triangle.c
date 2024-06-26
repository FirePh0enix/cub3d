/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 18:31:11 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer.h"
#include "shader.h"
#include <stdbool.h>
#include "rasterize_utils.h"

/*
 * Reference:
 * http://www.sunshine2k.de/coding/java/TriangleRasterization\
 /TriangleRasterization.html#algo1
 * https://www.youtube.com/watch?v=k5wtuKWmV48
 */

static inline void	put_to_buffers(t_rasterizer *rast, t_rparam rp,
	t_v2i a, t_v4 w)
{
	rast->r3d->color_buffer[rast->rect.min.x + a.x
		+ (rast->rect.min.y + a.y) * rast->r3d->width]
		= shader(rast->r3d, int_v2(rp.tri.t0, rp.tri.t1,
				rp.tri.t2, w), rp.image, rp.col);
	rast->depth_buffer[a.x + (rp.size.y - a.y - 1) * rp.size.x] = rp.z;
}

static inline void	draw_triangle(t_rasterizer *rast, t_rparam rp)
{
	int		i;
	int		j;
	t_v4	w;
	float	z;

	j = rp.rect.min.y - 1;
	while (++j <= rp.rect.max.y)
	{
		i = rp.rect.min.x - 1;
		while (++i <= rp.rect.max.x)
		{
			w = make_w(rp.tri, v3(i + 0.5f, j + 0.5f, 0.0));
			if (w.x >= 0 && w.y >= 0 && w.z >= 0)
			{
				w = v4(w.x / rp.area, w.y / rp.area, w.z / rp.area, 0);
				z = (w.x * rp.tri.v0.z + w.y * rp.tri.v1.z + w.z * rp.tri.v2.z);
				w.w = 1 / z;
				if (z < rast->depth_buffer[i + (rp.size.y - j - 1) * rp.size.x]
					|| z < 0.0 || z > 1.0)
					continue ;
				rp.z = z;
				put_to_buffers(rast, rp, v2i(i, j), w);
			}
		}
	}
}

static inline bool	calc_rect(t_tri tri, t_v2i size, t_rect *rect_)
{
	t_rect	rect;

	rect.min.x = min3f(tri.v0.x, tri.v1.x, tri.v2.x);
	rect.max.x = max3f(tri.v0.x, tri.v1.x, tri.v2.x);
	rect.min.y = min3f(tri.v0.y, tri.v1.y, tri.v2.y);
	rect.max.y = max3f(tri.v0.y, tri.v1.y, tri.v2.y);
	if (rect.min.x >= size.x || rect.min.y >= size.y
		|| rect.max.x < 0 || rect.max.y < 0)
		return (false);
	rect.min.x = fmaxf(rect.min.x, 0);
	rect.min.y = fmaxf(rect.min.y, 0);
	rect.max.x = fminf(rect.max.x, size.x - 1);
	rect.max.y = fminf(rect.max.y, size.y - 1);
	*rect_ = rect;
	return (true);
}

void	rasterize_triangle(t_rasterizer *rast, t_tri t, t_image *image,
	t_color col)
{
	const t_v2i	s = rasterizer_get_size(rast);
	t_rect		rect;
	float		area;

	t.v0 = mat4_multiply_v3(rast->projection_matrix, t.v0);
	t.v1 = mat4_multiply_v3(rast->projection_matrix, t.v1);
	t.v2 = mat4_multiply_v3(rast->projection_matrix, t.v2);
	if (t.v0.z < 0.1 || t.v1.z < 0.1 || t.v2.z < 0.1)
		return ;
	t.v0.x = (1 + t.v0.x) * 0.5 * s.x;
	t.v0.y = (1 + t.v0.y) * 0.5 * s.y;
	t.v1.x = (1 + t.v1.x) * 0.5 * s.x;
	t.v1.y = (1 + t.v1.y) * 0.5 * s.y;
	t.v2.x = (1 + t.v2.x) * 0.5 * s.x;
	t.v2.y = (1 + t.v2.y) * 0.5 * s.y;
	if (!calc_rect(t, s, &rect))
		return ;
	pint_v2(&t.t0, &t.t1, &t.t2, &t);
	t.v0.z = 1 / t.v0.z;
	t.v1.z = 1 / t.v1.z;
	t.v2.z = 1 / t.v2.z;
	area = edge_fn(t.v0, t.v1, t.v2);
	draw_triangle(rast, (t_rparam){.tri = t, .area = area, .size = s,
		.rect = rect, .image = image, .col = col});
}
