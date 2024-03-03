/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:43:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 23:43:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "fragment.h"

inline void	sort_ascend(t_v3 *v0, t_v3 *v1, t_v3 *v2)
{
	t_v3	tmp;

	if (v0->y > v1->y)
	{
		tmp = *v0;
		*v0 = *v1;
		*v1 = tmp;
	}
	if (v0->y > v2->y)
	{
		tmp = *v0;
		*v0 = *v2;
		*v2 = tmp;
	}
	if (v1->y > v2->y)
	{
		tmp = *v1;
		*v1 = *v2;
		*v2 = tmp;
	}
}

inline void	draw_hline(t_r3d *r3d, int sx, int mx, int y, float z, float z_step, t_color color)
{
	int	i;
	int	min;
	int	max;

	if (sx >= mx)
	{
		min = mx;
		max = sx;
	}
	else
	{
		min = sx;
		max = mx;
	}
	i = min;
	while (i <= max)
	{
		if (i < 0 || i >= r3d->width)
		{
			i++;
			continue ;
		}
		if (z > r3d->depth_buffer[i + y * r3d->width])
		{
			i++;
			z += z_step;
			continue ;
		}
		r3d->depth_buffer[i + y * r3d->width] = z;
		r3d->color_buffer[i + y * r3d->width] = r3d_fragment(color, (t_v2i){i, y});
		i++;
		z += z_step;
	}
}

inline void	fill_bottom_flat_triangle(t_r3d *r3d, t_stri tri, t_color color)
{
	float	x_step1, x_step2;
	float	z_step1, z_step2;
	float	curx1, curx2;
	float	z1, z2;
	int		scanline_y;

	x_step1 = (float)(tri.v1.x - tri.v0.x) / (float)(tri.v1.y - tri.v0.y);
	x_step2 = (float)(tri.v2.x - tri.v0.x) / (float)(tri.v2.y - tri.v0.y);
	z_step1 = (tri.d1 - tri.d0) / (float)(tri.v1.y - tri.v0.y);
	z_step2 = (tri.d2 - tri.d0) / (float)(tri.v2.y - tri.v0.y);
	curx1 = tri.v0.x;
	curx2 = tri.v0.x + 0.5;
	z1 = tri.d0;
	z2 = tri.d0;
	scanline_y = tri.v0.y;
	while (scanline_y <= tri.v1.y)
	{
		if (scanline_y < 0 || scanline_y >= r3d->height)
		{
			scanline_y++;
			continue ;
		}
		draw_hline(r3d, curx1, curx2, scanline_y, z1, (z1 - z2) / (curx2 - curx1), color);
		curx1 += x_step1;
		curx2 += x_step2;
		z1 -= z_step1;
		z2 -= z_step2;
		scanline_y++;
	}
}

inline void	fill_top_flat_triangle(t_r3d *r3d, t_stri tri, t_color color)
{
	float	x_step1, x_step2;
	float	z_step1, z_step2;
	float	curx1, curx2;
	float	z1, z2;
	int		scanline_y;

	x_step1 = (float)(tri.v2.x - tri.v0.x) / (float)(tri.v2.y - tri.v0.y);
	x_step2 = (float)(tri.v2.x - tri.v1.x) / (float)(tri.v2.y - tri.v1.y);
	z_step1 = (tri.d2 - tri.d0) / (float)(tri.v2.y - tri.v0.y);
	z_step2 = (tri.d2 - tri.d1) / (float)(tri.v2.y - tri.v1.y);
	curx1 = tri.v2.x;
	curx2 = tri.v2.x + 0.5;
	z1 = tri.d2;
	z2 = tri.d2;
	scanline_y = tri.v2.y;
	while (scanline_y > tri.v0.y)
	{
		if (scanline_y < 0 || scanline_y >= r3d->height)
		{
			scanline_y--;
			continue ;
		}
		draw_hline(r3d, curx1, curx2, scanline_y, z1, (z1 - z2) / (curx2 - curx1), color);
		curx1 -= x_step1;
		curx2 -= x_step2;
		z1 += z_step1; // TODO: maybe += here
		z2 += z_step2;
		scanline_y--;
	}
}

void	r3d_fill_triangle(t_r3d *r3d, t_tri tri, t_color color)
{
	t_v2i	v3;
	float	d3;
	t_stri	stri;

	sort_ascend(&tri.v0, &tri.v1, &tri.v2);
	stri = (t_stri){
		v3_to_v2i(tri.v0), v3_to_v2i(tri.v1), v3_to_v2i(tri.v2),
		tri.v0.z, tri.v1.z, tri.v2.z,
	};
	if (stri.v1.y == stri.v2.y)
		fill_bottom_flat_triangle(r3d, stri, color);
	else if (stri.v0.y == stri.v1.y)
		fill_top_flat_triangle(r3d, stri, color);
	else
	{
		d3 = 0.0;
		v3 = (t_v2i){((float)stri.v0.x + ((float)(stri.v1.y - stri.v0.y) / (float)(stri.v2.y - stri.v0.y)) * (float)(stri.v2.x - stri.v0.x)), stri.v1.y};
		fill_bottom_flat_triangle(r3d, (t_stri){stri.v0, stri.v1, v3, tri.v0.z, tri.v1.z, tri.v2.z}, color);
		fill_top_flat_triangle(r3d, (t_stri){stri.v1, v3, stri.v2, tri.v1.z, d3, tri.v2.z}, color);
	}
}
