/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/02 00:19:51 by ledelbec         ###   ########.fr       */
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
	float	t2 = *t;
	*t = *t / (1000.0 - 0.1) + 0.1; // the distance is normalized
	if (*t <= 0.1)
		return (false);
	q = v3_add(ray_pos, v3_scale(ray_dir, *t));

	t_v3	min = v3_sub(wall.pos, v3_scale(wall.size, 0.5));
	t_v3	max = v3_add(wall.pos, v3_scale(wall.size, 0.5));

	min = v3_scale(min, 1.0 / t2);
	max = v3_scale(max, 1.0 / t2);

	//printf("  q: %f %f %f\n", q.x, q.y, q.z);
	//printf("min: %f %f %f\n", min.x, min.y, min.z);
	//printf("max: %f %f %f\n", max.x, max.y, max.z);

	return (true);
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
		float px = (2 * (((x - r3d->width / 2.0) + 0.5) / r3d->width) - 1) * fov_tan * aspect_ratio;
		y = -1;
		while (++y < r3d->height)
		{
			float	py = (1 - 2 * (((y - r3d->height / 2.0) + 0.5) / r3d->height)) * fov_tan;
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
