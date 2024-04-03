/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/03 17:01:01 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"

static bool	wall_test_intersection(t_wall *wall, t_v3 ray_origin, t_v3 ray_dir,
	float *t, t_v3 *uv, t_v3 n, t_mat4 inv_trans, t_mat4 inv_rot)
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
	*uv = mat4_multiply_v3(inv_rot, q);
	*uv = mat4_multiply_v3(inv_trans, q);

	uv->x += wall->w / 2.0;
	uv->y += wall->h / 2.0;
	uv->x /= wall->w;// * *t;
	uv->y /= wall->h;// * *t;

	return (uv->x >= 0.0 && uv->x <= 1.0 && uv->y >= 0.0 && uv->y <= 1.0);
}

static t_color	sample_texture(t_image *img, t_v3 uv)
{
	int	x;
	int	y;

	x = uv.x * img->width;
	y = uv.y * img->height;
	return (hex(img->data[x + y * img->width]));
}

void	r3d_draw_wall(t_r3d *r3d, t_wall *wall)
{
	t_mat4		inv_trans;
	t_mat4		rot;
	t_mat4		inv_rot;
	const float	fov_tan = tanf(r3d->fov / 2.0 * M_PI / 180.0);
	const float	aspect_ratio = (float)r3d->width / (float)r3d->height;
	float		t;
	t_v3		uv;
	t_v3		n = v3(0.0, 0.0, -1.0);

	t_v3		camera_pos = v3(0.0, 0.0, 0.0);

	inv_trans = mat4_translation(v3_scale(wall->pos, -1));
	rot = mat4_rotation(v3(0, wall->rot_y, 0));
	inv_rot = mat4_rotation(v3_scale(v3(0, wall->rot_y, 0), -1));

	n = mat4_multiply_v3(rot, n);
	for (int x = 0; x < r3d->width; x++)
	{
		int		x2 = x;
		float	px = (2 * ((x2 + 0.5) / r3d->width) - 1) * fov_tan * aspect_ratio;

		for (int y = 0; y < r3d->width; y++)
		{
			int		y2 = y;
			float	py = (1 - 2 * ((y2 + 0.5) / r3d->height)) * fov_tan;
			t_v3	ray = v3_norm(v3(px, py, -1.0)); // TODO rotate the ray with the camera

			if (wall_test_intersection(wall, camera_pos, ray, &t, &uv, n, inv_trans, inv_rot)
				&& t > r3d->depth_buffer[x + y * r3d->width])
			{
				// printf("%f\n", t);
				r3d->depth_buffer[x + y * r3d->width] = t;
				r3d->color_buffer[x + y * r3d->width] = sample_texture(wall->img, uv);
			}
		}
	}
}
