/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:27:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 13:36:47 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"
#include "../math/mat4_init.h"

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height)
{
	r3d->canvas = mlx_new_image(mlx, width, height);
	r3d->width = width;
	r3d->height = height;
	r3d->fov = 70.0;
	r3d->mode = MODE_NORMAL;

	r3d->color_buffer = (void *) r3d->canvas->data;
	r3d->depth_buffer = (void *) ft_calloc(width * height * sizeof(float), 1);
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

t_v3	r3d_get_camera_dir(t_r3d *r3d)
{
	return (v3_norm(mat4_multiply_v3(mat4_rotation(r3d->camera->rotation), v3(0, 0, -1.0))));
}
