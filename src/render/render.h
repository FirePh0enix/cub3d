/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/19 23:01:50 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../math/vec.h"
# include "../math/matrix.h"
# include "mlx_int.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_vars	t_vars;

typedef struct s_tri
{
	t_v3	v0;
	t_v3	v1;
	t_v3	v2;

	t_v2	t0;
	t_v2	t1;
	t_v2	t2;

	t_v3	c0;
	t_v3	c1;
	t_v3	c2;
}	t_tri;

typedef union s_color
{
	unsigned int		raw;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	t;
	};
}	t_color;

t_color	hex(unsigned int hex);
t_color	rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char t);
t_color	rgbaf(float r, float g, float b, float t);
t_color	grayscalef(float f);
t_color	color_scale(t_color col, float f);

typedef struct s_mtl
{
	char	*name;
	t_img	*image;
}	t_mtl;

t_mtl	*mtl_load_from_file(t_vars *vars, char *filename);

typedef struct s_face
{
	int	v[3];
	int	t[3];
	int	n[3];
}	t_face;

typedef struct s_mesh
{
	t_mtl	*material;

	t_face	*faces;
	size_t	faces_count;

	t_v3	*vertices;
	size_t	vertices_count;

	t_v2	*textures;
	size_t	textures_count;
}	t_mesh;

/*
 * Load a Wavefront OBJ file and its associated mtl files into an usable mesh.
 */
t_mesh	*mesh_load_from_obj(t_vars *vars, char *filename);

/*
 * Validate indices for the mesh data. This means that indices can be used to
 * index the mesh data without any check without risking Out of Bounds.
 *
 * TODO
 */
bool	mesh_validate(t_mesh *mesh);

# ifdef RTHREADS

# include <pthread.h>

typedef struct s_r3d	t_r3d;

typedef struct s_job
{
	pthread_t	thread;
	t_r3d		*r3d;


	size_t		index;
	size_t		count;

	t_color		*color_buffer;
	float		*depth_buffer;
}	t_job;

typedef struct s_jobs
{
	t_job		jobs[RTHREADS];
	int			finished_jobs;

	t_mat4		translation;
	t_mat4		rotation;

	t_mesh		*mesh;
}	t_jobs;

void	r3d_mt_init(t_r3d *r3d);

/*
 * Draw a mesh using multithreading.
 */
void	r3d_mt_draw(t_r3d *r3d, t_mesh *mesh);

# endif

typedef enum e_mode
{
	MODE_NORMAL,
	MODE_WIREFRAME,
	MODE_DEPTH,
}	t_mode;

typedef struct s_r3d
{
	t_img			*canvas;
	t_mode			mode;

	float			fov;
	t_v3			camera_pos;
	
	t_color			*color_buffer;
	float			*depth_buffer;
	
	int				width;
	int				height;

	t_mat4			projection_matrix;
	float			rot_z;

# ifdef RTHREADS
	t_jobs			jobs;
# endif
}	t_r3d;

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
void	r3d_clear_depth_buffer(t_r3d *r3d);
void	r3d_clear_color_buffer(t_r3d *r3d, t_color color);

int		r3d_key_hook(int keycode, t_r3d *r3d);

typedef struct s_opts
{
	t_color	wireframe_color;
	t_color	solid_color;
	t_v3	offset;
}	t_opts;

void	r3d_draw_mesh(t_r3d *r3d, t_mesh *mesh, t_opts *opts);
void	r3d_fill_triangle(t_r3d *r3d, t_tri tri, t_mtl *mtl, t_color *cbuf, float *dbuf);


#endif
