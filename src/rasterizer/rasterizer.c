/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:23:56 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 15:23:50 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer.h"
#include <math.h>

void	rasterizer_init_overlay(t_rasterizer *rast, t_r3d *r3d, t_rect rect, float fov, t_alloc_table *at)
{
	t_v2i	size;

	rast->r3d = r3d;
	rast->overlay = true;
	rast->rect = rect;
	size = rasterizer_get_size(rast);
	rast->depth_buffer = salloc(at, size.x * size.y * sizeof(float));
	if (!rast->depth_buffer)
		return ;
	rast->projection_matrix = mat4_projection(fov, size.x, size.x);
}

t_v2i	rasterizer_get_size(t_rasterizer *rast)
{
	return ((t_v2i){rast->rect.max.x - rast->rect.min.x,
		rast->rect.max.y - rast->rect.min.y});
}

bool	rasterizer_is_overlay(t_rasterizer *rast)
{
	return (rast->overlay);
}

void	rasterizer_clear(t_rasterizer *rast)
{
	const t_v2i	size = rasterizer_get_size(rast);
	int			i;

	i = 0;
	while (i < size.x * size.y)
	{
		rast->depth_buffer[i] = -INFINITY;
		i++;
	}
}
