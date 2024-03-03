/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:27:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 19:26:38 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height)
{
	r3d->img = mlx_new_image(mlx, width, height);
	r3d->color_buffer = (t_color *) r3d->img->data;
	r3d->depth_buffer = (float *) malloc(sizeof(float) * width * height);
	r3d->width = width;
	r3d->height = height;
	r3d->camera_pos = (t_v3){};
	r3d->fov = 90.0;
	r3d->projection_matrix = mat4_projection(r3d->fov, width, height);
}
