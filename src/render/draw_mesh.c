/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:26:39 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/22 13:24:43 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../math/matrix.h"
#include "shader.h"
#include <math.h>
#include <stdbool.h>

/*
   https://www.youtube.com/watch?v=ih20l3pJoeU - Triangles & Projection
 */

void	draw_line(t_r3d *r3d, t_v3 v1, t_v3 v2, t_color color)
{
	float	dx, dy;
	float	x, y;
	float	step;
	int		i;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = v1.x;
	y = v1.y;
	i = 0;
	while (i <= step)
	{
		// FIXME This test is costing ~0.2 ms for the teapot !
		if ((int)x < 0 || (int)x >= r3d->width || (int)y < 0 || (int)y >= r3d->height)
		{
			i++;
			continue ;
		}
		r3d->color_buffer[(int)x + (r3d->height - (int)y) * r3d->width] = color;
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void	draw_triangle_wireframe(t_r3d *r3d, t_tri tri, t_color color)
{
	draw_line(r3d, tri.v0, tri.v1, color);
	draw_line(r3d, tri.v1, tri.v2, color);
	draw_line(r3d, tri.v2, tri.v0, color);
}

t_tri	tri_mul_mat4(t_tri tri, t_mat4 mat)
{
	tri.v0 = mat4_multiply_v3(mat, tri.v0);
	tri.v1 = mat4_multiply_v3(mat, tri.v1);
	tri.v2 = mat4_multiply_v3(mat, tri.v2);
	tri.n0 = mat4_multiply_v3(mat, tri.n0);
	tri.n1 = mat4_multiply_v3(mat, tri.n1);
	tri.n2 = mat4_multiply_v3(mat, tri.n2);
	return (tri);
}

static void	draw_debug_triangle(t_r3d *r3d, t_tri tri)
{
	const t_color	color = hex(0xFF00FFFF);

	tri = tri_mul_mat4(tri, r3d->projection_matrix);
	tri.v0.x = (1 + tri.v0.x) * 0.5 * r3d->width, tri.v0.y = (1 + tri.v0.y) * 0.5 * r3d->height;
	tri.v1.x = (1 + tri.v1.x) * 0.5 * r3d->width, tri.v1.y = (1 + tri.v1.y) * 0.5 * r3d->height;
	tri.v2.x = (1 + tri.v2.x) * 0.5 * r3d->width, tri.v2.y = (1 + tri.v2.y) * 0.5 * r3d->height;
	draw_triangle_wireframe(r3d, tri, color);
}

void	r3d_draw_mesh(t_r3d *r3d, t_mesh *mesh, t_opts *opts)
{
	const t_mat4	rotation = mat4_rotation(v3(0, r3d->rot_z, 0));
	const t_mat4	translation = mat4_translation((t_v3){0.0, -1.5, -4});
	const t_mat4	world = mat4_mul_mat4(translation, rotation);
	size_t			i;
	t_tri			tri;
	t_face			face;

	i = 0;
	while (i < mesh->faces_count)
	{
		face = mesh->faces[i];
		tri = (t_tri){
			mesh->vertices[face.v[0]], mesh->vertices[face.v[1]], mesh->vertices[face.v[2]],
			mesh->textures[face.t[0]], mesh->textures[face.t[1]], mesh->textures[face.t[2]],
			mesh->normals[face.n[0]], mesh->normals[face.n[1]], mesh->normals[face.n[2]],
		};

		tri = tri_mul_mat4(tri, world);

		t_v3	edge1, edge2, normal;
		edge1 = v3_sub(tri.v1, tri.v0);
		edge2 = v3_sub(tri.v2, tri.v0);
		normal = v3_norm(v3_cross(edge1, edge2));

		if (v3_dot(normal, v3_sub(tri.v0, r3d->camera_pos)) >= 0.0)
		{
			i++;
			continue ;
		}

		t_v3	light_dir = {{ 1.0, 0.0, 0.0 }};
		light_dir = v3_norm(light_dir);

		if (r3d->mode == MODE_WIREFRAME)
			draw_debug_triangle(r3d, tri);
		else
			r3d_fill_triangle(r3d, tri, mesh->material,
					r3d->color_buffer, r3d->depth_buffer, light_dir);
		i++;
	}
}
