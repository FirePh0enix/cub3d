/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:52:52 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/26 14:06:01 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	collide_aabb_vs_aabb(t_box a, t_box b)
{
	return (
		a.min.x <= b.max.x
		&& a.max.x >= b.min.x
		&& a.min.y <= b.max.y
		&& a.max.y >= b.min.y
		&& a.min.z <= b.max.z
		&& a.max.z >= b.min.z);
}

bool	collide_point_vs_aabb(t_v3 point, t_box b)
{
	return (
		point.x >= b.min.x
		&& point.x <= b.max.x
		&& point.y >= b.min.y
		&& point.y <= b.max.y
		&& point.z >= b.min.z
		&& point.z <= b.max.z);
}

bool	collide_wall(t_box player, int x, int y)
{
	t_box		tile_box;

	tile_box = box_from_wall(x, y);
	if (collide_aabb_vs_aabb(player, tile_box))
	{
		return (true);
	}
	return (false);
}

bool	collide_map(t_box player, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->tiles[x + y * map->width] != TILE_EMPTY
				&& map->tiles[x + y * map->width] != TILE_DOOR_OPEN)
			{
				if (collide_wall(player, x, y))
				{
					return (true);
				}
			}
			x++;
		}
		y++;
	}
	return (false);
}
