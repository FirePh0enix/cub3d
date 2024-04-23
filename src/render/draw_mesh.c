/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:26:39 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/13 00:01:18 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../math/matrix.h"
#include "shader.h"
#include "types.h"
#include "../scene.h"
#include <math.h>
#include <stdbool.h>

/*
   https://www.youtube.com/watch?v=ih20l3pJoeU - Triangles & Projection
 */

void	draw_line(t_r3d *r3d, t_v3 v1, t_v3 v2, t_color color)
{
	float	dx, dy, dz;
	float	x, y, z;
	float	step;
	int		i;
	ssize_t	index;

	v1.z = 1.0 / v1.z;
	v2.z = 1.0 / v2.z;
	dx = v2.x - v1.x;
	dy = v2.y - v1.y;
	dz = v2.z - v1.z;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	dz = dz / step;
	x = v1.x;
	y = v1.y;
	z = v1.z;
	i = 0;
	while (i <= step)
	{
		index = (int)x + (r3d->fb->height - (int)y) * r3d->fb->width;
		// FIXME This test is costing ~0.2 ms for the teapot !
		if (x < 0 || x > r3d->fb->width || y < 0 || y > r3d->fb->height 
			|| z < r3d->fb->depth[index])
		{
			x += dx;
			y += dy;
			z += dz;
			i++;
			continue ;
		}
		r3d->fb->depth[index] = z;
		r3d->fb->color[index] = color;
		x += dx;
		y += dy;
		z += dz;
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
	tri.v0.x = (1 + tri.v0.x) * 0.5 * r3d->fb->width, tri.v0.y = (1 + tri.v0.y) * 0.5 * r3d->fb->height;
	tri.v1.x = (1 + tri.v1.x) * 0.5 * r3d->fb->width, tri.v1.y = (1 + tri.v1.y) * 0.5 * r3d->fb->height;
	tri.v2.x = (1 + tri.v2.x) * 0.5 * r3d->fb->width, tri.v2.y = (1 + tri.v2.y) * 0.5 * r3d->fb->height;
	draw_triangle_wireframe(r3d, tri, color);
}

void	r3d_draw_mesh(t_r3d *r3d, t_scene *scene, t_mesh *mesh,
	t_camera *camera, t_transform transform)
{
	const t_mat4	rotation = mat4_rotation(transform.rotation);
	const t_mat4	translation = mat4_translation(transform.position);
	const t_mat4	camera_trans = mat4_translation(v3_scale(camera->position, -1));
	const t_mat4	world = mat4_mul_mat4(mat4_mul_mat4(translation, camera_trans), rotation);
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

		if (r3d->mode == MODE_WIREFRAME && !camera->fb)
			draw_debug_triangle(r3d, tri);
		else if (!camera->fb)
			r3d_fill_triangle(r3d, transform.position, tri, mesh->material,
					r3d->fb, scene->lights);
		else
			r3d_fill_triangle(r3d, transform.position, tri, mesh->material,
					camera->fb, scene->lights);
		i++;
	}
}
