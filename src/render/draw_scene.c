/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:53:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 15:08:21 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <math.h>
#include <stdbool.h>

inline void	put_pixel(t_r3d *r3d, t_color color, int sx, int sy)
{
	int	x;
	int	y;

	x = 0;
	while (x < r3d->scale)
	{
		y = 0;
		while (y < r3d->scale)
		{
			r3d->data[sx * r3d->scale + x + (sy * r3d->scale + y) * r3d->width] = color;
			y++;
		}
		x++;
	}
}

void	r3d_draw_scene(t_r3d *r3d, t_mesh *mesh)
{
	int		x;
	int		y;
	t_ray	ray;
	float	scale;
	float	aspect_ratio;
	t_color	color;
	float	ray_x;

	const int	width = r3d->width / r3d->scale;
	const int	height = r3d->height / r3d->scale;

	scale = tan((r3d->fov * 0.5) * 3.1415926535 / 180.0);
	aspect_ratio = (float)r3d->width / (float)r3d->height;
	x = 0;
	while (x < width)
	{
		// PERF: 0.5-1.0ms
		ray_x = (2.0 * ((x + 0.5) / (float)width) - 1) * aspect_ratio * scale;
		y = 0;
		while (y < height)
		{
			// TODO: The direction vector should be rotated.
			// TODO: The direction vector seems not to be required to be normalized
			// PERF: ~8ms
			ray = (t_ray){r3d->camera_pos, (t_v3){
				ray_x,
				(1 - 2.0 * ((y + 0.5) / (float)height)) * scale,
				-1.0,
			}};
			color = r3d_raycast_mesh(r3d, mesh, (t_consts){ray});
			if (color != 0xFF000000)
				put_pixel(r3d, color, x, y);
			y++;
		}
		x++;
	}
}
