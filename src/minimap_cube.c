/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_cube.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:00:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:04:30 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cub3d.h"
#include "rasterizer/rasterizer.h"

static void	draw_y(t_minimap *minimap, t_vars *vars, t_mat4 m)
{
	t_tri	tri1;
	t_tri	tri2;

	tri1 = (t_tri){.v0 = v3(-0.5, -0.5, -0.5), .v1 = v3(+0.5, -0.5, -0.5),
		.v2 = v3(-0.5, -0.5, +0.5), .t0 = (t_v2){1, 0}, .t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}};
	tri2 = (t_tri){.v0 = v3(+0.5, -0.5, -0.5), .v1 = v3(+0.5, -0.5, +0.5),
		.v2 = v3(-0.5, -0.5, +0.5), .t0 = (t_v2){1, 0}, .t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, vars->map.no, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri2, vars->map.no, hex(0x00DDDDDD));
	tri1 = (t_tri){.v0 = v3(-0.5, +0.5, -0.5), .v2 = v3(+0.5, +0.5, -0.5),
		.v1 = v3(-0.5, +0.5, +0.5), .t0 = (t_v2){1, 0}, .t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}};
	tri2 = (t_tri){.v0 = v3(+0.5, +0.5, -0.5), .v2 = v3(+0.5, +0.5, +0.5),
		.v1 = v3(-0.5, +0.5, +0.5), .t0 = (t_v2){1, 0}, .t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, vars->map.so, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri2, vars->map.so, hex(0x00DDDDDD));
}

static void	draw_x(t_minimap *minimap, t_vars *vars, t_mat4 m)
{
	t_tri	tri1;
	t_tri	tri2;

	tri1 = (t_tri){.v0 = v3(+0.5, -0.5, -0.5), .v1 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(+0.5, -0.5, +0.5), .t0 = (t_v2){1, 0}, .t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}};
	tri2 = (t_tri){.v0 = v3(+0.5, +0.5, -0.5), .v1 = v3(+0.5, +0.5, +0.5),
		.v2 = v3(+0.5, -0.5, +0.5), .t0 = (t_v2){1, 0}, .t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, vars->map.ea, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri2, vars->map.ea, hex(0x00DDDDDD));
	tri1 = (t_tri){.v0 = v3(-0.5, -0.5, -0.5), .v2 = v3(-0.5, +0.5, -0.5),
		.v1 = v3(-0.5, -0.5, +0.5), .t0 = (t_v2){1, 0}, .t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}};
	tri2 = (t_tri){.v0 = v3(-0.5, +0.5, -0.5), .v2 = v3(-0.5, +0.5, +0.5),
		.v1 = v3(-0.5, -0.5, +0.5), .t0 = (t_v2){1, 0}, .t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, vars->map.we, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri2, vars->map.we, hex(0x00DDDDDD));
}

void	minimap_draw_cube(t_minimap *minimap, t_vars *vars, t_v3 pos)
{
	const t_mat4	m = mat4_mul_mat4(mat4_rotation(
				v3(0, 0, minimap->rast.r3d->camera->rot.y)),
			mat4_translation(pos));
	t_tri			tri1;
	t_tri			tri2;

	tri1 = (t_tri){.v0 = v3(-0.5, -0.5, +0.5), .v1 = v3(+0.5, -0.5, +0.5),
		.v2 = v3(-0.5, +0.5, +0.5)};
	tri2 = (t_tri){.v0 = v3(+0.5, -0.5, +0.5), .v1 = v3(+0.5, +0.5, +0.5),
		.v2 = v3(-0.5, +0.5, +0.5)};
	mat4_mul_tri(m, &tri1, &tri2);
	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, NULL, hex(0x00222222));
	draw_y(minimap, vars, m);
	draw_x(minimap, vars, m);
}
