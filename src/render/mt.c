/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:34:11 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/19 23:08:46 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"
#include <pthread.h>

void	r3d_mt_init(t_r3d *r3d)
{
	int	id;

	id = 0;
	while (id < RTHREADS)
	{
		r3d->jobs.jobs[id].r3d = r3d;
		r3d->jobs.jobs[id].color_buffer = malloc(sizeof(t_color) * r3d->width * r3d->height);
		r3d->jobs.jobs[id].depth_buffer = malloc(sizeof(float) * r3d->width * r3d->height);
		id++;
	}
}

inline t_tri	tri_mul_mat4(t_tri tri, t_mat4 mat)
{
	tri.v0 = mat4_multiply_v3(mat, tri.v0);
	tri.v1 = mat4_multiply_v3(mat, tri.v1);
	tri.v2 = mat4_multiply_v3(mat, tri.v2);
	return (tri);
}

static void	job(t_job *job)
{
	const t_jobs	*jobs = &job->r3d->jobs;
	const t_mesh	*mesh = job->r3d->jobs.mesh;
	size_t			i;
	t_tri			tri;
	t_face			face;

	i = job->index;
	while (i < job->count)
	{
		face = mesh->faces[i];
		tri = (t_tri){
			mesh->vertices[face.v[0]], mesh->vertices[face.v[1]], mesh->vertices[face.v[2]],
			mesh->textures[face.t[0]], mesh->textures[face.t[1]], mesh->textures[face.t[2]],
			{}, {}, {}
		};

		tri = tri_mul_mat4(tri, jobs->rotation);
		tri = tri_mul_mat4(tri, jobs->translation);

		t_v3	edge1, edge2, normal;
		edge1 = v3_sub(tri.v1, tri.v0);
		edge2 = v3_sub(tri.v2, tri.v0);
		normal = v3_norm(v3_cross(edge1, edge2));

		if (v3_dot(normal, v3_sub(tri.v0, job->r3d->camera_pos)) >= 0.0)
		{
			i++;
			continue ;
		}

		t_v3	light_dir = { 0.0, 0.0, 1.0 };
		light_dir = v3_norm(light_dir);
		float	light_dot = v3_dot(light_dir, normal);

		r3d_fill_triangle(job->r3d, tri, mesh->material, job->color_buffer, job->depth_buffer);
		i++;
	}
	__atomic_fetch_add(&job->r3d->jobs.finished_jobs, 1, __ATOMIC_RELAXED);
}

static void	merge_buffers(t_r3d *r3d)
{
	int	id;
	int	x;
	int	y;
	int	index;

	id = 0;
	while (id < RTHREADS)
	{
		x = 0;
		while (x < r3d->width)
		{
			y = 0;
			while (y < r3d->height)
			{
				index = x + y * r3d->width;
				if (r3d->depth_buffer[index] > r3d->jobs.jobs[id].depth_buffer[index])
				{
					y++;
					continue ;
				}
				r3d->depth_buffer[index] = r3d->jobs.jobs[id].depth_buffer[index];
				r3d->color_buffer[index] = r3d->jobs.jobs[id].color_buffer[index];
				y++;
			}
			x++;
		}
		id++;
	}
}

void	r3d_mt_draw(t_r3d *r3d, t_mesh *mesh)
{
	const t_mat4	rotation = mat4_z_rot(r3d->rot_z);
	const t_mat4	translation = mat4_translation((t_v3){{0.0, 0.0, -6}});
	const size_t	faces_per_thread = mesh->faces_count / RTHREADS;
	int				id;
	size_t			face_start;

	face_start = 0;
	r3d->jobs.finished_jobs = 0;
	r3d->jobs.mesh = mesh;
	r3d->jobs.rotation = rotation;
	r3d->jobs.translation = translation;
	id = 0;
	while (id < RTHREADS)
	{
		ft_memset(r3d->jobs.jobs[id].color_buffer, 0, sizeof(t_color) * r3d->width * r3d->height);
		for (int i = 0; i < r3d->width * r3d->height; i++)
			r3d->jobs.jobs[id].depth_buffer[i] = INFINITY;
		r3d->jobs.jobs[id].index = face_start;
		if (id == RTHREADS)
			r3d->jobs.jobs[id].count = mesh->faces_count - face_start;
		else
			r3d->jobs.jobs[id].count = faces_per_thread;
		pthread_create(&r3d->jobs.jobs[id].thread, NULL, (void *) job, &r3d->jobs.jobs[id]);
		id++;
		face_start += faces_per_thread;
	}
	while (__atomic_load_n(&r3d->jobs.finished_jobs, __ATOMIC_RELAXED) != RTHREADS)
		;
	merge_buffers(r3d);
}
