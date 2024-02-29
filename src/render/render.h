/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/28 23:51:02 by ledelbec         ###   ########.fr       */
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
	int		width;
	int		height;
}	t_r3d;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}	t_ray;

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
void	r3d_raycast_triangle(t_r3d *r3d, t_triangle triangle);

#endif
