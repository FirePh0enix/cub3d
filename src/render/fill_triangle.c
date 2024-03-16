/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:43:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/17 00:35:36 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "fragment.h"

/*
 * Reference:
 * http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html#algo1
 *
 * FIXME:
 * - The depth testing is not 100% perfect, some artifacts can be seen when
 *   using the `Depth buffer` rendering mode. (fixed ?)
 * - Also even on a pertectly aligned cube, some pixels can be seen outside of
 *   triangles. (to check again)
 * - Texture is warped a little bit in one half of each triangles, can be seen
 *   better with the gold texture.
 */

inline void	swap2f(t_v2 *a, t_v2 *b)
{
	t_v2	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

inline void	swap3f(t_v3 *a, t_v3 *b)
{
	t_v3	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

inline void	sort_ascend(t_tri *tri)
{
	if (tri->v0.y > tri->v1.y)
	{
		swap3f(&tri->v0, &tri->v1);
		swap2f(&tri->t0, &tri->t1);
	}
	if (tri->v0.y > tri->v2.y)
	{
		swap3f(&tri->v0, &tri->v2);
		swap2f(&tri->t0, &tri->t2);
	}
	if (tri->v1.y > tri->v2.y)
	{
		swap3f(&tri->v1, &tri->v2);
		swap2f(&tri->t1, &tri->t2);
	}
}

inline void	draw_hline(
		t_r3d *r3d,
		int sx, int mx,
		int y,
		float z1, float z2,
		t_v2 uv1, t_v2 uv2,
		t_mtl *mtl)
{
	int		i;
	int		min;
	int		max;
	float	z_min, z_max, z_step, z;
	t_v2	uv_min, uv_max, uv_step, uv;
	int		index;

	if (sx >= mx)
	{
		min = mx;
		max = sx;
		z_min = z2;
		z_max = z1;
		uv_min = uv2;
		uv_max = uv1;
	}
	else
	{
		min = sx;
		max = mx;
		z_min = z1;
		z_max = z2;
		uv_min = uv1;
		uv_max = uv2;
	}
	i = min;

	z_step = (z_max - z_min) / (max + 1 - min);
	z = z_min;
	
	uv_step = (t_v2){
		(uv_max.x - uv_min.x) / (max + 1 - min),
		(uv_max.y - uv_min.y) / (max + 1 - min)
	};
	uv = uv_min;

	// printf("%f %f | %f %f\n", uv_min.x, uv_min.y, uv_max.x, uv_max.y);

	while (i <= max)
	{
		index = i + y * r3d->width;
		if (i < 0 || i >= r3d->width || r3d->depth_buffer[index] > z)
		{
			z += z_step;
			uv = v2_add(uv, uv_step);
			i++;
			continue ;
		}
		r3d->depth_buffer[index] = z;
		r3d->color_buffer[index] = r3d_fragment(r3d, mtl, z, uv);
		z += z_step;
		uv = v2_add(uv, uv_step);
		i++;
	}
}

void	fill_bottom_flat_triangle(t_r3d *r3d, t_stri tri, t_mtl *mtl)
{
	float	x_step1, x_step2;
	float	z_step1, z_step2;
	t_v2	uv_step1, uv_step2;
	float	curx1, curx2;
	float	z1, z2;
	t_v2	uv1, uv2;
	int		scanline_y;

	x_step1 = (float)(tri.v1.x - tri.v0.x) / (float)(tri.v1.y - tri.v0.y);
	x_step2 = (float)(tri.v2.x - tri.v0.x) / (float)(tri.v2.y - tri.v0.y);

	z_step1 = (tri.d1 - tri.d0) / (float)(tri.v1.y - tri.v0.y);
	z_step2 = (tri.d2 - tri.d0) / (float)(tri.v2.y - tri.v0.y);

	uv_step1 = (t_v2){
		(tri.t1.x - tri.t0.x) / (float)(tri.v1.y - tri.v0.y),
		(tri.t1.y - tri.t0.y) / (float)(tri.v1.y - tri.v0.y)
	};
	uv_step2 = (t_v2){
		(tri.t2.x - tri.t0.x) / (float)(tri.v2.y - tri.v0.y),
		(tri.t2.y - tri.t0.y) / (float)(tri.v2.y - tri.v0.y)
	};

	curx1 = tri.v0.x;
	curx2 = tri.v0.x + 0.5;

	z1 = tri.d0;
	z2 = tri.d0;

	uv1 = tri.t0;
	uv2 = tri.t0;

	scanline_y = fminf(tri.v0.y, r3d->height);
	while (scanline_y <= tri.v1.y)
	{
		if (scanline_y < 0 || scanline_y >= r3d->height)
		{
			curx1 += x_step1;
			curx2 += x_step2;
			z1 += z_step1;
			z2 += z_step2;
			uv1 = v2_add(uv1, uv_step1);
			uv2 = v2_add(uv2, uv_step2);
			scanline_y++;
			continue ;
		}
		draw_hline(r3d, curx1, curx2, scanline_y, z1, z2, uv1, uv2, mtl);
		curx1 += x_step1;
		curx2 += x_step2;
		z1 += z_step1;
		z2 += z_step2;
		uv1 = v2_add(uv1, uv_step1);
		uv2 = v2_add(uv2, uv_step2);
		scanline_y++;
	}
}

void	fill_top_flat_triangle(t_r3d *r3d, t_stri tri, t_mtl *mtl)
{
	float	x_step1, x_step2;
	float	z_step1, z_step2;
	t_v2	uv_step1, uv_step2;
	float	curx1, curx2;
	float	z1, z2;
	t_v2	uv1, uv2;
	int		scanline_y;

	x_step1 = (float)(tri.v2.x - tri.v0.x) / (float)(tri.v2.y - tri.v0.y);
	x_step2 = (float)(tri.v2.x - tri.v1.x) / (float)(tri.v2.y - tri.v1.y);

	z_step1 = (tri.d2 - tri.d0) / (float)(tri.v2.y - tri.v0.y);
	z_step2 = (tri.d2 - tri.d1) / (float)(tri.v2.y - tri.v1.y);

	uv_step1 = (t_v2){
		(tri.t2.x - tri.t0.x) / (float)(tri.v2.y - tri.v0.y),
		(tri.t2.y - tri.t0.y) / (float)(tri.v2.y - tri.v0.y)
	};
	uv_step2 = (t_v2){
		(tri.t2.x - tri.t1.x) / (float)(tri.v2.y - tri.v1.y),
		(tri.t2.y - tri.t1.y) / (float)(tri.v2.y - tri.v1.y)
	};

	curx1 = tri.v2.x;
	curx2 = tri.v2.x + 0.5;

	z1 = tri.d2;
	z2 = tri.d2;

	uv1 = tri.t2;
	uv2 = tri.t2;

	scanline_y = fmaxf(tri.v2.y, 0);
	while (scanline_y > tri.v0.y)
	{
		if (scanline_y < 0 || scanline_y >= r3d->height)
		{
			curx1 -= x_step1;
			curx2 -= x_step2;
			z1 -= z_step1;
			z2 -= z_step2;
			uv1 = v2_sub(uv1, uv_step1);
			uv2 = v2_sub(uv2, uv_step2);
			scanline_y--;
			continue ;
		}
		// printf("%f %f | %f %f\n", uv1.x, uv1.y, uv2.x, uv2.y);
		draw_hline(r3d, curx1, curx2, scanline_y, z1, z2, uv1, uv2, mtl);
		curx1 -= x_step1;
		curx2 -= x_step2;
		z1 -= z_step1;
		z2 -= z_step2;
		uv1 = v2_sub(uv1, uv_step1);
		uv2 = v2_sub(uv2, uv_step2);
		scanline_y--;
	}
}

void	r3d_fill_triangle(t_r3d *r3d, t_tri tri, t_mtl *mtl)
{
	t_v2i	v3;
	float	d3;
	t_v2	t3;
	t_stri	stri;

	sort_ascend(&tri);
	stri = (t_stri){
		v3_to_v2i(tri.v0), v3_to_v2i(tri.v1), v3_to_v2i(tri.v2),
		tri.v0.z, tri.v1.z, tri.v2.z,
		tri.t0, tri.t1, tri.t2,
	};
	if (stri.v1.y == stri.v2.y)
		fill_bottom_flat_triangle(r3d, stri, mtl);
	else if (stri.v0.y == stri.v1.y)
		fill_top_flat_triangle(r3d, stri, mtl);
	else
	{
		v3 = (t_v2i){
			((float)stri.v0.x + ((float)(stri.v1.y - stri.v0.y) / (float)(stri.v2.y - stri.v0.y)) * (float)(stri.v2.x - stri.v0.x)),
			stri.v1.y
		};
		d3 = stri.d0 + (float)(stri.v1.y - stri.v0.y) / (float)(stri.v2.y - stri.v0.y) * (float)(stri.d2 - stri.d0);
		t3 = (t_v2){
			stri.t0.x + (float)(stri.v1.y - stri.v0.y) / (float)(stri.v2.y - stri.v0.y) * (stri.t2.x - stri.t0.x),
			stri.t0.y + (float)(stri.v1.y - stri.v0.y) / (float)(stri.v2.y - stri.v0.y) * (stri.t2.y - stri.t0.y),
		};

		fill_bottom_flat_triangle(r3d, (t_stri){
				stri.v0, stri.v1, v3,
				tri.v0.z, tri.v1.z, d3,
				stri.t0, stri.t1, t3}, mtl);
		fill_top_flat_triangle(r3d, (t_stri){
				stri.v1, v3, stri.v2,
				tri.v1.z, d3, tri.v2.z,
				stri.t1, t3, stri.t2}, mtl);
	}
}
