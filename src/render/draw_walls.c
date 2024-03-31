/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/01 01:06:28 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline	bool	square_intersect(t_v3 ray_dir, t_v3 ray_pos,
	t_wall wall, float *t)
{
	t_v3	diff;
	float	p1;
	float	p2;
	t_v3	q;

	t_v3	pos = v3(0.0, 0.0, -10);

	diff = v3_sub(pos, ray_pos);
	p1 = v3_dot(diff, wall.n);
	p2 = v3_dot(ray_dir, wall.n);
	if (p2 <= 1e-6)
		return (false);
	*t = p1 / p2;
	if (*t <= 1e-6)
		return (false);
	q = v3_add(ray_pos, v3_scale(ray_dir, *t));
	*t = *t / (1000.0 - 0.1) + 0.1; // the distance is normalized

	float big_x = v3_dot(v3_sub(q, wall.v0), v3_sub(wall.v1, wall.v0)) / v3_length(v3_sub(wall.v1, wall.v0));
	float big_y = v3_dot(v3_sub(q, wall.v0), v3_sub(wall.v2, wall.v0)) / v3_length(v3_sub(wall.v2, wall.v0));

	return (big_x >= 0 && big_x <= 1 && big_y >= 0 && big_y <= 1);
}

void	r3d_draw_wall(t_r3d *r3d, t_wall wall)
{
	int			x;
	int			y;
	const float	aspect_ratio = (float)r3d->width / (float)r3d->height;
	const float	fov_tan = tanf(r3d->fov / 2.0 * M_PI / 180.0);

	x = -1;
	while (++x < r3d->width)
	{
		float	ndc_x = x - r3d->width / 2.0;
		float px = (2 * ((x + 0.5) / r3d->width) - 1) * fov_tan * aspect_ratio;
		y = -1;
		while (++y < r3d->height)
		{
			float	ndc_y = y - r3d->height / 2.0;

			float	py = (1 - 2 * ((y + 0.5) / r3d->height)) * fov_tan;
			t_v3	origin = v3(0.0, 0.0, 0.0);
			t_v3	dir = v3_norm(v3(px, py, -1));
			float	t;
			if (square_intersect(dir, origin, wall, &t)
					&& r3d->depth_buffer[x + y * r3d->width] <= t)
			{
				// printf("depth: %f\n", t);
				r3d->depth_buffer[x + y * r3d->width] = t;
				r3d->color_buffer[x + y * r3d->width] = hex(0xFF0000FF);
			}
		}
	}
}
