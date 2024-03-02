/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:26:39 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 22:31:27 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../math/matrix.h"
#include <math.h>
#include <stdbool.h>

typedef struct s_tri
{
	t_v3	v0;
	t_v3	v1;
	t_v3	v2;
}	t_tri;

/*
   https://www.youtube.com/watch?v=ih20l3pJoeU - Triangles & Projection
 */

void	draw_line(t_r3d *r3d, float x1, float y1, float x2, float y2)
{
	float	dx, dy;
	float	x, y;
	float	step;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		r3d->color_buffer[(int)x + (int)y * r3d->width] = 0xFFFFFFFF;
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void	draw_triangle(t_r3d *r3d, t_tri tri)
{
	draw_line(r3d, tri.v0.x, tri.v0.y, tri.v1.x, tri.v1.y);
	draw_line(r3d, tri.v1.x, tri.v1.y, tri.v2.x, tri.v2.y);
	draw_line(r3d, tri.v2.x, tri.v2.y, tri.v0.x, tri.v0.y);
}

void	r3d_draw_mesh(t_r3d *r3d, t_mesh *mesh)
{
	const t_mat4	projection = mat4_projection(90.0, 1280, 720);
	const t_mat4	rotation = mat4_z_rot(r3d->rot_z);
	size_t			i;
	t_tri			tri;

	i = 0;
	while (i < mesh->vertex_count)
	{
		tri = (t_tri){mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2]};
		tri = (t_tri){
			mat4_multiply_v3(rotation, tri.v0),
			mat4_multiply_v3(rotation, tri.v1),
			mat4_multiply_v3(rotation, tri.v2),
		};
		tri = (t_tri){
			mat4_multiply_v3(projection, tri.v0),
			mat4_multiply_v3(projection, tri.v1),
			mat4_multiply_v3(projection, tri.v2)
		};
		tri.v0.x += 1.0; tri.v0.y += 1.0;
		tri.v1.x += 1.0; tri.v1.y += 1.0;
		tri.v2.x += 1.0; tri.v2.y += 1.0;
		tri.v0.x *= 0.5 * r3d->width; tri.v0.y *= 0.5 * r3d->height;
		tri.v1.x *= 0.5 * r3d->width; tri.v1.y *= 0.5 * r3d->height;
		tri.v2.x *= 0.5 * r3d->width; tri.v2.y *= 0.5 * r3d->height;
		draw_triangle(r3d, tri);
		i += 3;
	}
}
