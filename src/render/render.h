/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 22:21:46 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../math/vec.h"
# include "mlx_int.h"
# include <stdbool.h>
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

typedef unsigned int	t_color;

typedef struct s_r3d
{
	t_img			*img;
	float			fov;
	
	t_v3			camera_pos;
	
	unsigned int	*color_buffer;
	float			*depth_buffer;
	
	int				width;
	int				height;

	float			rot_z;
}	t_r3d;

t_mesh	*mesh_load_from_data(t_v3 *vertices, size_t vertex_count);
void	mesh_destroy(t_mesh *mesh);

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
void	r3d_clear_depth_buffer(t_r3d *r3d);
void	r3d_clear_color_buffer(t_r3d *r3d, t_color color);
void	r3d_draw_mesh(t_r3d *r3d, t_mesh *mesh);

#endif
