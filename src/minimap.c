/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:10:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cub3d.h"
#include "math/mat4.h"
#include "math/mat4_init.h"
#include "math/mat4_mul.h"
#include "rasterizer/rasterizer.h"
#include "render/render.h"
#include "render/types.h"
#include <stdio.h>

static void	draw_character(t_minimap *minimap, t_v3 pos)
{
	const t_mat4	m = mat4_translation(pos);
	t_tri			tri1;

	tri1 = (t_tri){
		.v0 = v3(+0.0, -0.4, +0.4),
		.v1 = v3(+0.4, +0.4, +0.4),
		.v2 = v3(-0.4, +0.4, +0.4),
	};
	tri1.v0 = mat4_multiply_v3(m, tri1.v0);
	tri1.v1 = mat4_multiply_v3(m, tri1.v1);
	tri1.v2 = mat4_multiply_v3(m, tri1.v2);
	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00FFFFFF));
}

static void	draw_floor(t_minimap *minimap, t_vars *vars, t_v3 pos)
{
	const t_mat4	m = mat4_mul_mat4(mat4_rotation(
				v3(0, 0, minimap->rast.r3d->camera->rot.y)),
			mat4_translation(pos));
	t_tri			tri;
	t_tri			tri2;

	tri = (t_tri){
		.v0 = v3(-0.5, -0.5, -0.5), .v1 = v3(+0.5, -0.5, -0.5),
		.v2 = v3(-0.5, +0.5, -0.5), .t0 = (t_v2){0, 0},
		.t1 = (t_v2){1, 0}, .t2 = (t_v2){0, 1}};
	tri2 = (t_tri){
		.v0 = v3(+0.5, -0.5, -0.5), .v1 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(-0.5, +0.5, -0.5), .t0 = (t_v2){1, 0},
		.t1 = (t_v2){1, 1}, .t2 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri, &tri2);
	rasterize_triangle(&minimap->rast, tri, vars->map.floor_image,
		vars->map.floor_color);
	rasterize_triangle(&minimap->rast, tri2, vars->map.floor_image,
		vars->map.floor_color);
}

static void	draw_background(t_minimap *minimap, t_r3d *r3d, t_rect rect)
{
	int		x;
	int		y;
	t_color	col;

	x = 0;
	while (x < rect.max.x - rect.min.x)
	{
		y = 0;
		while (y < rect.max.y - rect.min.y)
		{
			col = r3d->color[(rect.min.x + x) + (rect.min.y + y) * r3d->w];
			r3d->color[(rect.min.x + x) + (rect.min.y + y) * r3d->w]
				= blend(minimap->bg, col);
			y++;
		}
		x++;
	}
}

static void	draw_something(t_r3d *r3d, t_minimap *m, t_vars *vars,
	t_v2i p)
{
	if (m->map->tiles[p.x + p.y * m->map->width] != TILE_EMPTY
		&& m->map->tiles[p.x + p.y * m->map->width] != TILE_DOOR
		&& m->map->tiles[p.x + p.y * m->map->width] != TILE_DOOR_OPEN)
		minimap_draw_cube(m, vars, v3_sub(v3(p.x, p.y, -8),
				v3(r3d->camera->pos.x - 0.5, r3d->camera->pos.z - 0.5, 0)));
	else if (m->map->tiles[p.x + p.y * m->map->width] == TILE_DOOR)
	{
		draw_floor(m, vars, v3_sub(v3(p.x, p.y, -8),
				v3(r3d->camera->pos.x - 0.5, r3d->camera->pos.z - 0.5, 0)));
		minimap_draw_door(m, vars, v3_sub(v3(p.x, p.y, -8),
				v3(r3d->camera->pos.x - 0.5, r3d->camera->pos.z - 0.5, 0)));
	}
	else if (m->map->tiles[p.x + p.y * m->map->width] == TILE_DOOR_OPEN)
		draw_floor(m, vars, v3_sub(v3(p.x, p.y, -8),
				v3(r3d->camera->pos.x - 0.5, r3d->camera->pos.z - 0.5, 0)));
	else
		draw_floor(m, vars, v3_sub(v3(p.x, p.y, -8),
				v3(r3d->camera->pos.x - 0.5, r3d->camera->pos.z - 0.5, 0)));
}

void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_vars *vars)
{
	int	x;
	int	y;

	rasterizer_clear(&minimap->rast);
	draw_background(minimap, minimap->rast.r3d, minimap->rast.rect);
	x = 0;
	while (x < minimap->map->width)
	{
		y = 0;
		while (y < minimap->map->height)
		{
			draw_something(r3d, minimap, vars, v2i(x, y));
			y++;
		}
		x++;
	}
	draw_character(minimap, v3(-0.0, -0.0, -8));
}
