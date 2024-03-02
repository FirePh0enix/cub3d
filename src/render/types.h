/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:15:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 12:30:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "../math/vec.h"
# include "mlx_int.h"
# include <stddef.h>
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

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}	t_ray;

typedef unsigned int	t_color;

typedef struct s_r3d
{
	t_img			*buffer;
	unsigned int	*data;
	int				width;
	int				height;
	int				scale;
	float			fov;
	t_v3			camera_pos;
}	t_r3d;

typedef struct s_consts
{
	t_ray	ray;
}	t_consts;

#endif
