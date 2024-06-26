/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:17:32 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 23:47:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "../cub3d.h"

static void	draw_line(t_r3d *r3d, t_map *map, t_vars *vars, t_dl_param p)
{
	double	perp_wall_dist;
	t_image	*texture;
	int		draw_start;
	int		draw_end;
	int		line_height;

	if (p.side == 0)
		perp_wall_dist = (p.side_dist_x - p.delta_dist_x);
	else
		perp_wall_dist = (p.side_dist_y - p.delta_dist_y);
	line_height = (int)(r3d->h / perp_wall_dist);
	draw_start = maxi2(-line_height / 2 + r3d->h / 2, 0);
	draw_end = mini2(line_height / 2 + r3d->h / 2, r3d->h - 1);
	if (map->tiles[p.map_x + p.map_y * map->width] == TILE_DOOR)
		texture = vars->door;
	else
		texture = texture_for_wall(map, p.side,
				v2i(vars->map.player->base.transform.position.x,
					vars->map.player->base.transform.position.z),
				v2i(p.map_x, p.map_y));
	draw_each_pixels(r3d, texture, (t_ep_param){p.side, perp_wall_dist,
		p.ray_dir_x, p.ray_dir_y, line_height, draw_start, draw_end, p.x});
}

static void	raycast_world2(t_r3d *r3d, t_rw_param p, t_v2i *_step,
	t_v2 *_side_dist)
{
	t_v2i	step;
	t_v2	side_dist;

	if (p.ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (r3d->camera->pos.x - p.map_pos.x) * p.dd.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (p.map_pos.x + 1.0 - r3d->camera->pos.x) * p.dd.x;
	}
	if (p.ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (r3d->camera->pos.z - p.map_pos.y) * p.dd.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (p.map_pos.y + 1.0 - r3d->camera->pos.z) * p.dd.y;
	}
	*_step = step;
	*_side_dist = side_dist;
}

static void	raycast_world4(t_v2 *side_dist, t_rw_param *p, t_v2i step,
	int *side)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += p->dd.x;
		p->map_pos.x += step.x;
		*side = 0;
	}
	else
	{
		side_dist->y += p->dd.y;
		p->map_pos.y += step.y;
		*side = 1;
	}
}

static void	raycast_world3(t_r3d *r3d, t_map *map, t_vars *vars, t_rw_param p)
{
	int		hit;
	int		side;
	t_v2i	step;
	t_v2	side_dist;

	hit = 0;
	raycast_world2(r3d, p, &step, &side_dist);
	while (hit == 0)
	{
		raycast_world4(&side_dist, &p, step, &side);
		if (p.map_pos.x < 0 || p.map_pos.x >= map->width || p.map_pos.y < 0
			|| p.map_pos.y >= map->height)
			break ;
		if ((map->tiles[p.map_pos.x + p.map_pos.y * map->width] >= TILE_FULL
				&& map->tiles[p.map_pos.x + p.map_pos.y * map->width] <= TILE_9)
			|| map->tiles[p.map_pos.x + p.map_pos.y * map->width] == TILE_DOOR)
			hit = 1;
	}
	if (hit)
		draw_line(r3d, map, vars, (t_dl_param){side, side_dist.x,
			side_dist.y, p.dd.x, p.dd.y, p.map_pos.x, p.map_pos.y,
			p.ray_dir.x, p.ray_dir.y, p.x});
}

void	r3d_raycast_world(t_r3d *r3d, t_map *map, t_vars *vars)
{
	int		x;
	double	camera_x;
	t_v2	ray_dir;
	t_v2i	map_pos;
	t_v2	delta_dist;

	raycast_floor_and_ceiling(r3d, map);
	x = 0;
	while (x < r3d->w)
	{
		camera_x = 2 * x / (double)r3d->w - 1;
		ray_dir.x = r3d->camera->dir_x + r3d->camera->plane_x * camera_x;
		ray_dir.y = r3d->camera->dir_y + r3d->camera->plane_y * camera_x;
		map_pos.x = (int)r3d->camera->pos.x;
		map_pos.y = (int)r3d->camera->pos.z;
		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		raycast_world3(r3d, map, vars,
			(t_rw_param){map_pos, delta_dist, ray_dir, x});
		x++;
	}
	raycast_entities(r3d, vars);
}
