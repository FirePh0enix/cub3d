/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 00:17:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../math/vec.h"
# include "mlx.h"
# include "mlx_int.h"
# include <stddef.h>

typedef struct s_triangle
{
	t_v3	v0;
	t_v3	v1;
	t_v3	v2;
}	t_triangle;

typedef struct s_mesh
{
	t_v3	*vertices;
	size_t	vertex_count;
}	t_mesh;

t_mesh	*mesh_load_from_data(t_v3 *vertices, size_t vertex_count);
void	mesh_destroy(t_mesh *mesh);

typedef struct s_r3d
{
	t_img	*buffer;
	unsigned int	*data;
	int		width;
	int		height;
	int		scale;
	float	fov;
	t_v3	camera_pos;
}	t_r3d;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}	t_ray;

/*
 Per pixel values.
 */
typedef struct s_consts
{
	t_ray	ray;
}	t_consts;

typedef unsigned int	t_color;

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
t_color	r3d_raycast_mesh(t_r3d *r3d, t_mesh *mesh, t_consts consts);

void	r3d_draw_scene(t_r3d *r3d, t_mesh *mesh);

#endif
