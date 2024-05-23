/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/22 16:18:37 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "../math/utils.h"
#include "../cub3d.h"
#include "types.h"
#include <stdio.h>

static inline bool	wall_test_intersection(t_r3d *r3d, t_wall *wall, t_v3 ray_origin,
	t_v3 ray_dir, float *t, t_v3 *uv, t_v3 *pos, t_v3 n, t_mat4 inv_trans)
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
	// t_v3	projected_pos = project_pos(r3d, q);
	// projected_pos.z = -1.0 / q.z;
	// FIXME Works way better if the point is not projected for some reason
	*t = -1.0 / q.z;
	return (uv->x >= 0.0 && uv->x <= 1.0 && uv->y >= 0.0 && uv->y <= 1.0);
}

static inline t_color	sample_texture(t_r3d *r3d, t_image *img, t_v3 uv)
{
	int	x;
	int	y;

	if (!img)
		return (hex(0x00FFFFFF));
	x = uv.x * (img->width - 1);
	y = img->height - 1 - uv.y * (img->height - 1);
	x = clampf(x, 0, img->width - 1);
	y = clampf(y, 0, img->height - 1);
	return (hex(img->data[x + y * img->width]));
}

static inline void	set_pixel(t_r3d *r3d, int x, int y, t_color col,
	float t, t_v3 n, t_v3 pos, t_light *lights)
{
	// const t_v3	light = v3(1.0, 1.0, 1.0); //compute_lighting(r3d, lights, pos, v3_scale(n, -1));
	int			index;

	// col.r *= light.r;
	// col.g *= light.g;
	// col.b *= light.b;
	index = x + y * r3d->width;
	if (t < r3d->fb->depth[index])
		return ;
	r3d->fb->depth[index] = t;
	if (r3d->mode == MODE_DEPTH)
		r3d->fb->color[index] = grayscalef(t);
	else
		r3d->fb->color[index] = col;
}

void	r3d_draw_wall(t_r3d *r3d, t_wall *wall, t_light *lights, t_v2i min, t_v2i max)
{
	float			t;
	t_v3			uv;
	t_v3			pos;
	const t_v3		camera_pos = r3d->camera->position;
	int				x;
	int				y;

	x = min.x - 1;
	while (++x < max.x + 1)
	{
		float	px = (2 * ((x * 1 + 0.5) / r3d->width) - 1) * r3d->tan2_fov * r3d->aspect_ratio;

		y = min.y - 1;
		while (++y < max.y + 1)
		{
			float	py = (1 - 2 * ((y * 1 + 0.5) / r3d->height)) * r3d->tan2_fov;
			t_v3	ray = (v3(px, py, -1.0));
			// TODO rotate the ray with the camera

			if (wall_test_intersection(r3d, wall, camera_pos, ray, &t, &uv, &pos,
				wall->n, wall->inverse_position))
				set_pixel(r3d, x, y, sample_texture(r3d, wall->img, uv), t, wall->n, pos, lights);
		}
	}
}

static bool	project_corners(t_r3d *r3d, t_wall wall, t_v2i *min, t_v2i *max)
{
	const t_mat4	mat = mat4_mul_mat4(wall.position, wall.rotation);
	t_tri			tri;

	tri.v0 = v3(-WALL_SIZE / 2, -WALL_SIZE / 2, 0.0);
	tri.v1 = v3(WALL_SIZE / 2, -WALL_SIZE / 2, 0.0);
	tri.v2 = v3(WALL_SIZE / 2, WALL_SIZE / 2, 0.0);

	// Transform the vertices
	tri.v0 = mat4_multiply_v3(mat, tri.v0);
	tri.v1 = mat4_multiply_v3(mat, tri.v1);
	tri.v2 = mat4_multiply_v3(mat, tri.v2);

	// Project the vertices
	tri.v0 = mat4_multiply_v3(r3d->projection_matrix, tri.v0);
	tri.v1 = mat4_multiply_v3(r3d->projection_matrix, tri.v1);
	tri.v2 = mat4_multiply_v3(r3d->projection_matrix, tri.v2);

	// Convert from screen space to NDC then raster (in one go)
	tri.v0.x = (1 + tri.v0.x) * 0.5 * r3d->fb->width, tri.v0.y = (1 + tri.v0.y) * 0.5 * r3d->fb->height;
	tri.v1.x = (1 + tri.v1.x) * 0.5 * r3d->fb->width, tri.v1.y = (1 + tri.v1.y) * 0.5 * r3d->fb->height;
	tri.v2.x = (1 + tri.v2.x) * 0.5 * r3d->fb->width, tri.v2.y = (1 + tri.v2.y) * 0.5 * r3d->fb->height;

	int	min_x, max_x, min_y, max_y;

	min_x = min3f(tri.v0.x, tri.v1.x, tri.v2.x);
	max_x = max3f(tri.v0.x, tri.v1.x, tri.v2.x);
	min_y = min3f(tri.v0.y, tri.v1.y, tri.v2.y);
	max_y = max3f(tri.v0.y, tri.v1.y, tri.v2.y);

	if (min_x >= r3d->fb->width || min_y >= r3d->fb->height || max_x < 0 || max_y < 0)
		return (false);

	min->x = min_x;
	min->y = min_y;
	max->x = max_x;
	max->y = max_y;

	return (true);
}

void	r3d_draw_walls(t_r3d *r3d, t_map *map)
{
	int		i;
	t_wall	*wall;
	t_v2i	min;
	t_v2i	max;

	i = 0;
	while (i < map->width * map->height)
	{
		wall = &map->walls[i].so;

		if (map->walls[i].is_empty)
		{
			i++;
			continue ;
		}

		if (v3_length_squared(v3_sub(r3d->camera->position, wall->pos)) >= WALL_RENDER_DISTANCE * WALL_RENDER_DISTANCE)
		{
			i++;
			continue ;
		}

		if (!project_corners(r3d, map->walls[i].so, &min, &max))
		{
			i++;
			continue ;
		}

		r3d_draw_wall(r3d, &map->walls[i].so, NULL, min, max);
		i++;
	}
}
