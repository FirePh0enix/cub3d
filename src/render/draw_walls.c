/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/05 12:24:19 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"

/*
 * Project the position to NDC screen space using matrices.
 */
static inline t_v3	project_pos(t_r3d *r3d, t_v3 pos)
{
	pos = mat4_multiply_v3(r3d->projection_matrix, pos);
	return (pos);
}

static inline bool	wall_test_intersection(t_r3d *r3d, t_wall *wall, t_v3 ray_origin,
	t_v3 ray_dir, float *t, t_v3 *uv, t_v3 n, t_mat4 inv_trans)
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
	if (*t <= 0.1)
		return (false);
	*uv = mat4_multiply_v3(wall->inverse_rotation, q);
	*uv = mat4_multiply_v3(inv_trans, *uv);
	uv->x += wall->w / 2.0;
	uv->y += wall->h / 2.0;
	uv->x /= wall->w;
	uv->y /= wall->h;

	// FIXME(opt) Dont need the entire matrix multiplication, only for the z
	//            component.
	*t = -1.0 / project_pos(r3d, q).z;
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

static inline void	set_pixel(t_r3d *r3d, int x, int y, t_color col,
	int scale, float t)
{
	int	i;
	int	j;
	int	xx;
	int	yy;
	int	index;

	i = -1;
	while (++i < scale)
	{
		j = -1;
		while (++j < scale)
		{
			xx = x * scale + i;
			yy = r3d->height - y * scale + j;
			index = xx + yy * r3d->width;
			if (t < r3d->depth_buffer[index])
				continue ;
			r3d->depth_buffer[index] = t;
			r3d->color_buffer[index] = col;
		}
	}
}

void	r3d_draw_wall(t_r3d *r3d, t_wall *wall)
{
	t_mat4		inv_trans;
	float		t;
	t_v3		uv;
	t_v3		camera_pos = v3(0.0, 0.0, 0.0);
	int			x;
	int			y;

	inv_trans = mat4_translation(v3_scale(wall->pos, -1));
	x = -1;
	while (++x < r3d->width / SCALE)
	{
		float	px = (2 * ((x * SCALE + 0.5) / r3d->width) - 1) * r3d->tan2_fov * r3d->aspect_ratio;

		y = -1;
		while (++y < r3d->height / SCALE)
		{
			float	py = (1 - 2 * ((y * SCALE + 0.5) / r3d->height)) * r3d->tan2_fov;
			t_v3	ray = (v3(px, py, -1.0));
			// TODO rotate the ray with the camera
			// It seems to work without normalizing the vector, v2_norm costs ~10ms

			if (wall_test_intersection(r3d, wall, camera_pos, ray, &t, &uv,
				wall->n, inv_trans))
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
