/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/24 12:09:45 by ledelbec         ###   ########.fr       */
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

	min.x = fmaxf(0, min.x);
	max.x = fminf(r3d->width - 1, max.x);
	min.y = fmaxf(0, min.y);
	max.y = fminf(r3d->height - 1, max.y);

	// min.x = 0;
	// min.y = 0;
	// max.x = 1280 - 1;
	// max.y = 720 - 1;

	x = min.x - 1;
	while (++x < max.x + 1)
	{
		float	px = (2 * ((x * 1 + 0.5) / r3d->width) - 1) * r3d->tan2_fov * r3d->aspect_ratio;

		y = min.y - 1;
		while (++y < max.y + 1)
		{
			float	py = (1 - 2 * ((y * 1 + 0.5) / r3d->height)) * r3d->tan2_fov;
			t_v3	ray = v3(px, py, -1.0);
			// TODO rotate the ray with the camera

			// r3d->fb->color[x + y * r3d->fb->width] = hex(0x000000FF);
			if (wall_test_intersection(r3d, wall, camera_pos, ray, &t, &uv, &pos,
				wall->n, wall->inverse_position))
				set_pixel(r3d, x, y, sample_texture(r3d, wall->img, uv), t, wall->n, pos, lights);
		}
	}
}

static bool	project_corners(t_r3d *r3d, t_wall *wall, t_v2i *min, t_v2i *max)
{
	const float		half_size = WALL_SIZE / 2;
	const t_mat4	model_mat = mat4_mul_mat4(wall->position, wall->rotation);
	const t_mat4	camera_trans = mat4_translation(v3_scale(r3d->camera->position, -1));
	const t_mat4	world_mat = mat4_mul_mat4(camera_trans, model_mat);

	t_v3		p0 = v3(-half_size,  half_size, 0.0);
	t_v3		p1 = v3( half_size,  half_size, 0.0);
	t_v3		p2 = v3( half_size, -half_size, 0.0);
	t_v3		p3 = v3(-half_size, -half_size, 0.0);

	p0 = mat4_multiply_v3(world_mat, p0);
	p1 = mat4_multiply_v3(world_mat, p1);
	p2 = mat4_multiply_v3(world_mat, p2);
	p3 = mat4_multiply_v3(world_mat, p3);

	p0 = mat4_multiply_v3(r3d->projection_matrix, p0);
	p1 = mat4_multiply_v3(r3d->projection_matrix, p1);
	p2 = mat4_multiply_v3(r3d->projection_matrix, p2);
	p3 = mat4_multiply_v3(r3d->projection_matrix, p3);

	p0.x = (1 + p0.x) * 0.5 * r3d->fb->width, p0.y = (1 + p0.y) * 0.5 * r3d->fb->height;
	p1.x = (1 + p1.x) * 0.5 * r3d->fb->width, p1.y = (1 + p1.y) * 0.5 * r3d->fb->height;
	p2.x = (1 + p2.x) * 0.5 * r3d->fb->width, p2.y = (1 + p2.y) * 0.5 * r3d->fb->height;
	p3.x = (1 + p3.x) * 0.5 * r3d->fb->width, p3.y = (1 + p3.y) * 0.5 * r3d->fb->height;

	min->x = fminf(p0.x, fminf(p1.x, fminf(p2.x, p3.x)));
	max->x = fmaxf(p0.x, fmaxf(p1.x, fmaxf(p2.x, p3.x)));
	min->y = fminf(p0.y, fminf(p1.y, fminf(p2.y, p3.y)));
	max->y = fmaxf(p0.y, fmaxf(p1.y, fmaxf(p2.y, p3.y)));

	if (min->x >= r3d->width || min->y >= r3d->height || max->x < 0 || max->y < 0)
		return (false);
	return (true);
}

static void	draw_one_wall(t_r3d *r3d, t_wall *wall)
{
	t_v2i	min;
	t_v2i	max;

	if (v3_length_squared(v3_sub(r3d->camera->position, wall->pos)) >= WALL_RENDER_DISTANCE * WALL_RENDER_DISTANCE)
		return ;
	// if (!project_corners(r3d, wall, &min, &max))
	// 	return ;
	r3d_draw_wall(r3d, wall, NULL, min, max);
}

void	r3d_draw_walls(t_r3d *r3d, t_map *map)
{
	int		i;

	i = 0;
	while (i < map->width * map->height)
	{
		if (map->walls[i].is_empty)
		{
			i++;
			continue ;
		}
		draw_one_wall(r3d, &map->walls[i].so);
		// draw_one_wall(r3d, &map->walls[i].ea);
		draw_one_wall(r3d, &map->walls[i].we);
		i++;
	}
}
