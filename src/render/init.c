/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:27:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 16:26:25 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height)
{
	r3d->canvas = mlx_new_image(mlx, width, height);
	r3d->width = width;
	r3d->height = height;
	r3d->fb = create_fb(width, height);
	free(r3d->fb->color);
	r3d->fb->color = (void *) r3d->canvas->data;
	r3d->camera_pos = (t_v3){};
	r3d->fov = 70.0;
	r3d->projection_matrix = mat4_projection(r3d->fov, width, height);
	r3d->mode = MODE_NORMAL;
	r3d->tan2_fov = tanf(r3d->fov / 2.0 * M_PI / 180.0);
	r3d->aspect_ratio = (float)width / (float)height;
}

int	r3d_key_hook(int keycode, t_r3d *r3d)
{
	if (keycode == XK_F1)
		r3d->mode = MODE_NORMAL;
	else if (keycode == XK_F2)
		r3d->mode = MODE_WIREFRAME;
	else if (keycode == XK_F3)
		r3d->mode = MODE_DEPTH;
	return (0);
}
