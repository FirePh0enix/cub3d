/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:43:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 13:51:54 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "fragment.h"

inline void	sort_ascend(t_stri tri, t_v2i *v0, t_v2i *v1, t_v2i *v2)
{
	t_v2i	tmp;

	*v0 = tri.v0;
	*v1 = tri.v1;
	*v2 = tri.v2;
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

inline void	draw_hline(t_r3d *r3d, int sx, int mx, int y, t_color color)
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
		r3d->color_buffer[i + y * r3d->width] = r3d_fragment(color, (t_v2i){i, y});
		i++;
	}
}

inline void	fill_bottom_flat_triangle(t_r3d *r3d, t_v2i v0, t_v2i v1, t_v2i v2, t_color color)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	invslope1 = (float)(v1.x - v0.x) / (float)(v1.y - v0.y);
	invslope2 = (float)(v2.x - v0.x) / (float)(v2.y - v0.y);
	curx1 = v0.x;
	curx2 = v0.x + 0.5;
	scanline_y = v0.y;
	while (scanline_y <= v1.y)
	{
		draw_hline(r3d, curx1, curx2, scanline_y, color);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline_y++;
	}
}

inline void	fill_top_flat_triangle(t_r3d *r3d, t_v2i v0, t_v2i v1, t_v2i v2, t_color color)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	invslope1 = (float)(v2.x - v0.x) / (float)(v2.y - v0.y);
	invslope2 = (float)(v2.x - v1.x) / (float)(v2.y - v1.y);
	curx1 = v2.x;
	curx2 = v2.x + 0.5;
	scanline_y = v2.y;
	while (scanline_y > v0.y)
	{
		draw_hline(r3d, curx1, curx2, scanline_y, color);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline_y--;
	}
}

void	r3d_fill_triangle(t_r3d *r3d, t_stri tri, t_color color)
{
	t_v2i	v0, v1, v2;
	t_v2i	v3;

	sort_ascend(tri, &v0, &v1, &v2);
	if (v1.y == v2.y)
		fill_bottom_flat_triangle(r3d, v0, v1, v2, color);
	else if (v0.y == v1.y)
		fill_top_flat_triangle(r3d, v0, v1, v2, color);
	else
	{
		v3 = (t_v2i){((float)v0.x + ((float)(v1.y - v0.y) / (float)(v2.y - v0.y)) * (float)(v2.x - v0.x)), v1.y};
		fill_bottom_flat_triangle(r3d, v0, v1, v3, color);
		fill_top_flat_triangle(r3d, v1, v3, v2, color);
	}
}
