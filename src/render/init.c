/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:47:19 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 22:49:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"
#include <math.h>

void	r3d_init(t_r3d *r3d, void *mlx, t_v2i size, t_alloc_table *at)
{
	r3d->canvas = mlx_new_image(mlx, size.x, size.y);
	r3d->width = size.x;
	r3d->height = size.y;
	r3d->fov = 70.0;
	r3d->mode = MODE_NORMAL;
	r3d->color_buffer = (void *) r3d->canvas->data;
	r3d->depth_buffer = scalloc(at, size.x * size.y * sizeof(float), 1);
	if (!r3d)
		return ;
}

int	r3d_key_hook(int keycode, t_r3d *r3d)
{
	if (keycode == XK_F1)
		r3d->mode = MODE_NORMAL;
	else if (keycode == XK_F2)
		r3d->mode = MODE_DEPTH;
	return (0);
}

void	r3d_clear_depth_buffer(t_r3d *r3d)
{
	const int	size = r3d->width * r3d->height;
	int			i;

	i = 0;
	while (i < size)
	{
		r3d->depth_buffer[i] = INFINITY;
		i++;
	}
}

void	r3d_clear_color_buffer(t_r3d *r3d, t_color color)
{
	const int	size = r3d->width * r3d->height;
	int			i;

	i = 0;
	while (i < size)
	{
		r3d->color_buffer[i] = color;
		i++;
	}
}
