/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phoenix <phoenix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:03:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/27 00:42:34 by phoenix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"
#include "shader.h"
#include "types.h"
#include <X11/Xlib.h>
#include <stdio.h>

// static inline void	set_pixel(t_r3d *r3d, int x, int y, t_color col,
// 	float t, t_v3 n, t_v3 pos, t_light *lights)
// {
// 	// const t_v3	light = v3(1.0, 1.0, 1.0); //compute_lighting(r3d, lights, pos, v3_scale(n, -1));
// 	int			index;

// 	// col.r *= light.r;
// 	// col.g *= light.g;
// 	// col.b *= light.b;
// 	index = x + y * r3d->width;
// 	if (t < r3d->fb->depth[index])
// 		return ;
// 	r3d->fb->depth[index] = t;
// 	if (r3d->mode == MODE_DEPTH)
// 		r3d->fb->color[index] = grayscalef(t);
// 	else
// 		r3d->fb->color[index] = col;
// }

/*
	https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/shadingwithsurfacenormals
 */

static inline bool	hit_wall(t_r3d *r3d, t_ray *r, t_wall *w, t_v2 *r_uv, float *r_depth)
{
	t_v3 p0 = w->p0;
	t_v3 p1 = w->p1;
	t_v3 p2 = w->p2;

	t_v3 dp10 = v3_sub(p1, p0);
	t_v3 dp20 = v3_sub(p2, p0);
	t_v3 n = v3_cross(dp10, dp20);

	float n_dot_r = v3_dot(n, r->dir);

	if (fabs(n_dot_r) < 1e-6)
	{
		return (false);
	}

	float t = -v3_dot(n, v3_sub(r->origin, p0)) / n_dot_r;
	t_v3 m = v3_add(r->origin, v3_scale(r->dir, t));

	// Don't print pixels the camera can't see
	if (v3_dot(v3_sub(m, r->origin), r->dir) <= 0.0)
	{
		return (false);
	}

	t_v3 dmp1 = v3_sub(m, p0);
	float u = v3_dot(dmp1, dp10);
	float v = v3_dot(dmp1, dp20);

	float max_u = v3_dot(dp10, dp10);
	float max_v = v3_dot(dp20, dp20);

	r_uv->x = u / max_u;
	r_uv->y = v / max_v;

	*r_depth = -1.0 / m.z;
	*r_depth = *r_depth;

	return (u >= 0.0 && u <= max_u && v >= 0.0 && v <= max_v);
}

static t_v3 calc_ray(t_r3d *r3d, t_mat4 inv_projection, int x, int y)
{
	float ndc_x = (2.0 * x) / r3d->fb->width - 1.0;
	float ndc_y = 1.0 - (2.0 * y) / r3d->fb->height;
	float ndc_z = 1.0;

	t_v3 ray_clip = v3(ndc_x, ndc_y, ndc_z);
	t_v3 ray_world = mat4_multiply_v3(inv_projection, ray_clip);
	t_v3 ray_dir = v3_sub(v3_norm(ray_world), r3d->camera->position);
	return (ray_dir);
}

void	r3d_raycast_wall(t_r3d *r3d, t_wall *wall, t_light *lights, t_v2i min, t_v2i max)
{
	t_v2	uv;
	float	d;

	min.x = fmaxf(min.x, 0);
	min.y = fmaxf(min.y, 0);
	max.x = fminf(max.x, r3d->fb->width - 1);
	max.y = fminf(max.y, r3d->fb->height - 1);

	min.x = 0;
	min.y = 0;
	max.x = r3d->fb->width - 1;
	max.y = r3d->fb->height - 1;

	int	y = min.y;
	int	x;
	while (y <= max.y)
	{
		x = min.x;
		while (x <= max.x)
		{
			float	px = (2 * ((x * 1 + 0.5) / r3d->width) - 1) * r3d->tan2_fov * r3d->aspect_ratio;
			float	py = (1 - 2 * ((y * 1 + 0.5) / r3d->height)) * r3d->tan2_fov;

			// t_ray r = { r3d->camera->position, v3_norm(v3(px, py, -1.0)) };
			// https://stackoverflow.com/questions/2354821/raycasting-how-to-properly-apply-a-projection-matrix

			// t_v3 pos = v3((float)x / r3d->width * 2.0 - 1.0, (float)y / r3d->height * 2.0 - 1.0, 0);
			// t_v3 dir = mat4_multiply_v3(inv_projection, v3(pos * (Z_FAR)));
			// t_ray r = { r3d->camera->position, dir };

			t_ray r = { r3d->camera->position, v3(px, py, -1.0) };

			if (hit_wall(r3d, &r, wall, &uv, &d) && d >= r3d->fb->depth[x + y * r3d->fb->width])
			{
				r3d->fb->color[x + y * r3d->fb->width] = sample(wall->material, uv);
				r3d->fb->depth[x + y * r3d->fb->width] = d;
			}
			x++;
		}
		y++;
	}
}

void	r3d_draw_wall(t_r3d *r3d, t_wall *wall, t_light *lights)
{
	const t_transform transform = { .position = wall->pos, .rotation = v3(0, M_PI + wall->rot_y, 0) };

	(void) lights;
	r3d_draw_triangle(r3d, r3d->camera, wall->t0, transform, wall->material);
	r3d_draw_triangle(r3d, r3d->camera, wall->t1, transform, wall->material);
}

static bool	project_corners(t_r3d *r3d, t_wall *wall, t_v2i *min, t_v2i *max)
{
	const float		half_size = WALL_SIZE / 2;
	const t_mat4	model_mat = mat4_mul_mat4(mat4_translation(wall->pos), mat4_rotation(v3(0, wall->rot_y, 0)));
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

#ifndef _BONUS
	if (v3_length_squared(v3_sub(r3d->camera->position, wall->pos)) >= WALL_RENDER_DISTANCE * WALL_RENDER_DISTANCE)
		return ;
	if (!project_corners(r3d, wall, &min, &max))
		return ;
	r3d_raycast_wall(r3d, wall, NULL, min, max);
#else
	(void) min;
	(void) max;
	if (wall->hide)
		return ;
	r3d_draw_wall(r3d, wall, NULL);
#endif
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
		draw_one_wall(r3d, &map->walls[i].no);
		draw_one_wall(r3d, &map->walls[i].so);
		draw_one_wall(r3d, &map->walls[i].ea);
		draw_one_wall(r3d, &map->walls[i].we);
		i++;
	}
}
