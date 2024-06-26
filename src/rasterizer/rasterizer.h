/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:14:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 14:37:14 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERIZER_H
# define RASTERIZER_H

# include "../math/matrix.h"
# include "../math/vec.h"
# include "../render/render.h"

typedef struct s_tri
{
	t_v3	v0;
	t_v3	v1;
	t_v3	v2;

	t_v2	t0;
	t_v2	t1;
	t_v2	t2;

	t_v3	n0;
	t_v3	n1;
	t_v3	n2;
}	t_tri;

typedef void	(*t_effect)(t_v2i pos, t_color col);

typedef struct s_rect
{
	t_v2i	min;
	t_v2i	max;
}	t_rect;

typedef struct s_rasterizer
{
	t_r3d		*r3d;
	t_mat4		projection_matrix;
	t_rect		rect;
	t_effect	effect;

	bool		overlay;
	bool		flip;
	float		*depth_buffer;
}	t_rasterizer;

/*
	Create a rasterizer which works as an overlay on the raycasting, managing
	its own depth buffer.
 */
void	rasterizer_init_overlay(t_rasterizer *rast, t_r3d *r3d,
			t_rect rect, float fov);

void	rasterizer_clear(t_rasterizer *rast);

t_v2i	rasterizer_get_size(t_rasterizer *rast);
bool	rasterizer_is_overlay(t_rasterizer *rast);

void	rasterize_triangle(t_rasterizer *rast, t_tri tri,
			t_image *image, t_color col);

#endif
