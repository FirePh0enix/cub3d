/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:19:27 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 20:13:45 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"

t_image	*texture_for_wall(t_vars *vars, int side, t_v2i p, t_v2i t)
{
	if (vars->map.tiles[t.x + t.y * vars->map.width] >= TILE_2
		&& vars->map.tiles[t.x + t.y * vars->map.width] <= TILE_9)
		return (vars->tiles[
				vars->map.tiles[t.x + t.y * vars->map.width] - TILE_2]);
	if (side == 0 && p.x >= t.x)
		return (vars->map.ea);
	else if (side == 0 && p.x < t.x)
		return (vars->map.we);
	else if (side == 1 && p.y < t.y)
		return (vars->map.no);
	else if (side == 1 && p.y >= t.y)
		return (vars->map.so);
	return (vars->map.no);
}

void	draw_each_pixels(t_r3d *r3d, t_image *texture, t_ep_param p)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;

	if (p.side == 0)
		wall_x = r3d->camera->pos.z + p.perp_wall_dist * p.ray_dir_y;
	else
		wall_x = r3d->camera->pos.x + p.perp_wall_dist * p.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * texture->w;
	if (p.side == 0 && p.ray_dir_x > 0)
		tex_x = texture->w - tex_x - 1;
	else if (p.side == 1 && p.ray_dir_y < 0)
		tex_x = texture->w - tex_x - 1;
	step = 1.0 * texture->h / p.line_height;
	tex_pos = (p.draw_start - r3d->h / 2.0 + p.line_height / 2.0) * step;
	while (p.draw_start < p.draw_end)
	{
		r3d->color[p.x + p.draw_start * r3d->w]
			= ((t_color *)texture->data)[tex_x + (int)tex_pos * texture->w];
		tex_pos += step;
		p.draw_start++;
	}
	r3d->depth[p.x] = p.perp_wall_dist;
}
