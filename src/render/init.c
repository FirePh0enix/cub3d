/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:27:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 14:58:18 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"
#include "../math/mat4_init.h"

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height, t_alloc_table *at)
{
	r3d->canvas = mlx_new_image(mlx, width, height);
	r3d->width = width;
	r3d->height = height;
	r3d->fov = 70.0;
	r3d->mode = MODE_NORMAL;

	r3d->color_buffer = (void *) r3d->canvas->data;
	r3d->depth_buffer = (void *) scalloc(at, width * height * sizeof(float), 1);
	if (!r3d)
		return ; // TODO: Free the renderer
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

