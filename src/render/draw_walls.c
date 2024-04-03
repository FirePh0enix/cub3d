/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/04 00:40:47 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"

static inline bool	wall_test_intersection(t_wall *wall, t_v3 ray_origin, t_v3 ray_dir,
	float *t, t_v3 *uv, t_v3 n, t_mat4 inv_trans)
{
	t_v3	diff;
	float	p1;
	float	p2;
	t_v3	q;

	diff = v3_sub(wall->pos, ray_origin);
	p1 = v3_dot(diff, n);
	p2 = v3_dot(ray_dir, n);
	if (p2 <= 1e-6)
		return (false);
	*t = p1 / p2;
	q = v3_add(ray_origin, v3_scale(ray_dir, *t));
	*t = *t / (1000.0 - 0.1) + 0.1; // the distance is normalized. this is needed
									// for the depth buffer
	if (*t <= 0.1)
		return (false);
	*uv = mat4_multiply_v3(wall->inverse_rotation, q);
	*uv = mat4_multiply_v3(inv_trans, q);
	uv->x += wall->w / 2.0;
	uv->y += wall->h / 2.0;
	uv->x /= wall->w;
	uv->y /= wall->h;
	return (uv->x >= 0.0 && uv->x <= 1.0 && uv->y >= 0.0 && uv->y <= 1.0);
}

static inline t_color	sample_texture(t_image *img, t_v3 uv)
{
	int	x;
	int	y;

	x = uv.x * (img->width);
	y = img->height - uv.y * (img->height);
	return (hex(img->data[x + y * img->width]));
}

#define SCALE 2

static inline void	set_pixel(t_r3d *r3d, int x, int y, t_color col,
	int scale, float t)
{
	int	i;
	int	j;
	int	xx;
	int	yy;

	// printf("t = %f\n", t);
	i = -1;
	while (++i < scale)
	{
		j = -1;
		while (++j < scale)
		{
			if (t < r3d->depth_buffer[x + y * r3d->width])
				continue ;
			xx = x * scale + i;
			yy = y * scale + j;
			r3d->depth_buffer[xx + yy * r3d->width] = t;
			r3d->color_buffer[xx + yy * r3d->width] = col;
		}
	}
}

void	r3d_draw_wall(t_r3d *r3d, t_wall *wall)
{
	t_mat4		inv_trans;
	const float	aspect_ratio = (float)r3d->width / (float)r3d->height;
	float		t;
	t_v3		uv;
	t_v3		n = v3(0.0, 0.0, -1.0);
	t_v3		camera_pos = v3(0.0, 0.0, 0.0);

	inv_trans = mat4_translation(v3_scale(wall->pos, -1));
	n = mat4_multiply_v3(wall->rotation, n);
	for (int x = 0; x < r3d->width / SCALE; x++)
	{
		float	px = (2 * ((x * SCALE + 0.5) / r3d->width) - 1) * r3d->tan2_fov * aspect_ratio;

		for (int y = 0; y < r3d->width / SCALE; y++)
		{
			float	py = (1 - 2 * ((y * SCALE + 0.5) / r3d->height)) * r3d->tan2_fov;
			t_v3	ray = (v3(px, py, -1.0)); // TODO rotate the ray with the camera
											  // It seems to work without normalizing the vector, v2_norm costs ~10ms

			if (wall_test_intersection(wall, camera_pos, ray, &t, &uv,
				n, inv_trans))
				set_pixel(r3d, x, y, sample_texture(wall->img, uv), SCALE, t);
		}
	}
}

void	r3d_draw_walls(t_r3d *r3d, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->width * map->height)
		r3d_draw_wall(r3d, &map->walls[i]);
}
