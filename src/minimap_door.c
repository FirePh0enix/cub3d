/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:18:10 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/06 17:02:32 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"
#include "rasterizer/rasterizer.h"

void	mat4_mul_tri(t_mat4 m, t_tri *tri1, t_tri *tri2)
{
	tri1->v0 = mat4_multiply_v3(m, tri1->v0);
	tri1->v1 = mat4_multiply_v3(m, tri1->v1);
	tri1->v2 = mat4_multiply_v3(m, tri1->v2);
	tri2->v0 = mat4_multiply_v3(m, tri2->v0);
	tri2->v1 = mat4_multiply_v3(m, tri2->v1);
	tri2->v2 = mat4_multiply_v3(m, tri2->v2);
}

static void	draw_y(t_minimap *minimap, t_vars *vars, t_mat4 m)
{
	t_tri	tri1;
	t_tri	tri2;

	tri1 = (t_tri){.v0 = v3(-0.5, -0.2, -0.5), .v1 = v3(+0.5, -0.2, -0.5),
		.v2 = v3(-0.5, -0.2, +0.5), .t0 = (t_v2){0, 0}, .t1 = (t_v2){1, 0},
		.t2 = (t_v2){0, 1}};
	tri2 = (t_tri){.v0 = v3(+0.5, -0.2, -0.5), .v1 = v3(+0.5, -0.2, +0.5),
		.v2 = v3(-0.5, -0.2, +0.5), .t0 = (t_v2){1, 0}, .t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, vars->door, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, vars->door, hex(0x00222222));
	tri1 = (t_tri){.v0 = v3(-0.5, +0.2, -0.5), .v2 = v3(+0.5, +0.2, -0.5),
		.v1 = v3(-0.5, +0.2, +0.5), .t0 = (t_v2){0, 0}, .t2 = (t_v2){1, 0},
		.t1 = (t_v2){0, 1}};
	tri2 = (t_tri){.v0 = v3(+0.5, +0.2, -0.5), .v2 = v3(+0.5, +0.2, +0.5),
		.v1 = v3(-0.5, +0.2, +0.5), .t0 = (t_v2){1, 0}, .t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, vars->door, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, vars->door, hex(0x00222222));
}

static void	draw_x(t_minimap *minimap, t_vars *vars, t_mat4 m)
{
	t_tri	tri1;
	t_tri	tri2;

	(void) vars;
	tri1 = (t_tri){.v0 = v3(+0.5, -0.2, -0.5), .v1 = v3(+0.5, +0.2, -0.5),
		.v2 = v3(+0.5, -0.2, +0.5)};
	tri2 = (t_tri){.v0 = v3(+0.5, +0.2, -0.5), .v1 = v3(+0.5, +0.2, +0.5),
		.v2 = v3(+0.5, -0.2, +0.5)};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, NULL, hex(0x00222222));
	tri1 = (t_tri){.v0 = v3(-0.5, -0.2, -0.5), .v2 = v3(-0.5, +0.2, -0.5),
		.v1 = v3(-0.5, -0.2, +0.5)};
	tri2 = (t_tri){.v0 = v3(-0.5, +0.2, -0.5), .v2 = v3(-0.5, +0.2, +0.5),
		.v1 = v3(-0.5, -0.2, +0.5)};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, NULL, hex(0x00222222));
}

void	minimap_draw_door(t_minimap *minimap, t_vars *vars, t_v3 pos, float rot_y)
{
	(void) rot_y;
	const t_mat4	m = mat4_mul_mat4(mat4_rotation(
				v3(0, 0, minimap->rast.r3d->camera->rot.y)),
			mat4_mul_mat4(mat4_translation(pos), mat4_rotation(v3(0, 0, rot_y))));
	t_tri			tri1;
	t_tri			tri2;

	tri1 = (t_tri){.v0 = v3(-0.5, -0.2, +0.5), .v1 = v3(+0.5, -0.2, +0.5),
		.v2 = v3(-0.5, +0.2, +0.5)};
	tri2 = (t_tri){.v0 = v3(+0.5, -0.2, +0.5), .v1 = v3(+0.5, +0.2, +0.5),
		.v2 = v3(-0.5, +0.2, +0.5)};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, NULL, hex(0x00222222));
	draw_y(minimap, vars, m);
	draw_x(minimap, vars, m);
}
