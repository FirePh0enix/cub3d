/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:43:53 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 23:44:18 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_floor(t_r3d *r3d, t_cf_param p)
{
	t_v2i	t;

	if (p.img)
	{
		t.x = (int)(p.img->w * (p.floor.x - p.cell.x)) & (p.img->w - 1);
		t.y = (int)(p.img->h
				* (p.floor.y - p.cell.y)) & (p.img->h - 1);
	}
	if (!p.img)
		r3d->color[p.p.x + p.p.y * r3d->w] = p.col;
	else
		r3d->color[p.p.x + p.p.y * r3d->w]
			= p.img->data[t.x + t.y * p.img->w];
}

static void	draw_ceiling(t_r3d *r3d, t_cf_param p)
{
	t_v2i	t;

	if (p.img)
	{
		t.x = (int)(p.img->w * (p.floor.x - p.cell.x)) & (p.img->w - 1);
		t.y = (int)(p.img->h
				* (p.floor.y - p.cell.y)) & (p.img->h - 1);
	}
	if (!p.img)
		r3d->color[p.p.x + (r3d->h - p.p.y - 1) * r3d->w]
			= p.col;
	else
		r3d->color[p.p.x + (r3d->h - p.p.y - 1) * r3d->w]
			= p.img->data[t.x + t.y * p.img->w];
}

static void	raycast_floor_and_ceiling2(t_r3d *r3d, t_map *map, t_cf2_param p)
{
	t_v2			floor_step;
	t_v2			floor;
	float			raw_distance;
	t_v2i			cell;
	int				x;

	raw_distance = (0.5 * r3d->h) / (int)(p.y - r3d->h / 2);
	floor_step.x = raw_distance * (p.ray_dir1.x - p.ray_dir0.x) / r3d->w;
	floor_step.y = raw_distance * (p.ray_dir1.y - p.ray_dir0.y) / r3d->w;
	floor.x = r3d->camera->pos.x + raw_distance * p.ray_dir0.x;
	floor.y = r3d->camera->pos.z + raw_distance * p.ray_dir0.y;
	x = 0;
	while (x < r3d->w)
	{
		cell.x = (int)(floor.x);
		cell.y = (int)(floor.y);
		draw_floor(r3d, (t_cf_param){(void *) map->floor_image,
			map->floor_color, cell, floor, v2i(x, p.y)});
		draw_ceiling(r3d, (t_cf_param){(void *) map->ceilling_image,
			map->ceiling_color, cell, floor, v2i(x, p.y)});
		floor.x += floor_step.x;
		floor.y += floor_step.y;
		x++;
	}
}

void	raycast_floor_and_ceiling(t_r3d *r3d, t_map *map)
{
	int				y;
	t_v2			ray_dir0;
	t_v2			ray_dir1;

	y = 0;
	while (y < r3d->h)
	{
		ray_dir0.x = r3d->camera->dir_x - r3d->camera->plane_x;
		ray_dir0.y = r3d->camera->dir_y - r3d->camera->plane_y;
		ray_dir1.x = r3d->camera->dir_x + r3d->camera->plane_x;
		ray_dir1.y = r3d->camera->dir_y + r3d->camera->plane_y;
		raycast_floor_and_ceiling2(r3d, map,
			(t_cf2_param){ray_dir0, ray_dir1, y});
		y++;
	}
}
