/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:47:19 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 23:08:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"
#include <math.h>

void	r3d_init(t_r3d *r3d, void *mlx, t_v2i size, t_alloc_table *at)
{
	r3d->canvas = mlx_new_image(mlx, size.x, size.y);
	r3d->w = size.x;
	r3d->h = size.y;
	r3d->fov = 70.0;
	r3d->color = (void *) r3d->canvas->data;
	r3d->depth = scalloc(at, size.x * size.y * sizeof(float), 1);
	if (!r3d)
		return ;
}

void	r3d_clear_depth_buffer(t_r3d *r3d)
{
	const int	size = r3d->w * r3d->h;
	int			i;

	i = 0;
	while (i < size)
	{
		r3d->depth[i] = INFINITY;
		i++;
	}
}

void	r3d_clear_color_buffer(t_r3d *r3d, t_color color)
{
	const int	size = r3d->w * r3d->h;
	int			i;

	i = 0;
	while (i < size)
	{
		r3d->color[i] = color;
		i++;
	}
}
