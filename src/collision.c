/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:52:52 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/30 16:30:22 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math/v3.h"
#include "render/render.h"
#include "scene.h"
#include <complex.h>

bool	collide(t_box a, t_box b)
{
	return (
		a.min.x <= b.max.x
		&& a.max.x >= b.min.x
		&& a.min.y <= b.max.y
		&& a.max.y >= b.min.y
		&& a.min.z <= b.max.z
		&& a.max.z >= b.min.z);
}

t_box	box_from_entity(t_entity *entity)
{
	t_box	box;

	box.min.x = entity->transform.position.x - entity->width / 2;
	box.max.x = entity->transform.position.x + entity->width / 2;
	box.min.y = entity->transform.position.y - entity->height / 2;
	box.max.y = entity->transform.position.y + entity->height / 2;
	box.min.z = entity->transform.position.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + entity->depth / 2;
	return (box);
}

t_box	box_from_velocity(t_entity *entity)
{
	const t_v3	vel = entity->velocity;
	t_box		box;

	box.min.x = entity->transform.position.x + vel.x - entity->width / 2;
	box.max.x = entity->transform.position.x + vel.x + entity->width / 2;
	box.min.y = entity->transform.position.y + vel.y - entity->height / 2;
	box.max.y = entity->transform.position.y + vel.y + entity->height / 2;
	box.min.z = entity->transform.position.z + vel.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + vel.z + entity->depth / 2;
	return (box);
}

t_box	box_from_wall(int x, int y)
{
	t_box	box;

	box.min.x = x * WALL_SIZE - WALL_SIZE / 2;
	box.max.x = x * WALL_SIZE + WALL_SIZE / 2;
	box.min.y = -WALL_SIZE / 2;
	box.max.y = +WALL_SIZE / 2;
	box.min.z = y * WALL_SIZE - WALL_SIZE / 2;
	box.max.z = y * WALL_SIZE + WALL_SIZE / 2;
	return (box);
}

bool	collide_with_wall(t_entity *player, t_map *map, int x, int y)
{
	int			t;
	t_box		player_box;
	t_box		tile_box;

	t = map->tiles[x + y * map->width];
	if (t == TILE_FULL)
	{
		player_box = box_from_velocity(player);
		tile_box = box_from_wall(x, y);
		if (collide(player_box, tile_box))
			return (true);
	}
	return (false);
}

bool collide_with_map(t_player *player, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->tiles[x + y * map->width] == TILE_FULL)
			{
				if (collide_with_wall(&player->base, map, x, y))
					return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void	adjust_player_pos(t_player *player, t_map *map)
{
	const float	precision = 0.01;

	while (collide_with_map(player, map))
	{
		printf(CYAN"COLLIDE X\n"RESET);
		if (player->base.velocity.x > 0)
			player->base.velocity.x -= precision;
		else if (player->base.velocity.x < 0)
			player->base.velocity.x += precision;
	}
	while (collide_with_map(player, map))
	{
		printf(CYAN"COLLIDE Y\n"RESET);
		if (player->base.velocity.y > 0)
			player->base.velocity.y -= precision;
		else if (player->base.velocity.y < 0)
			player->base.velocity.y += precision;
	}
	while (collide_with_map(player, map))
	{
		printf(CYAN"COLLIDE Z\n"RESET);
		if (player->base.velocity.z > 0)
			player->base.velocity.z -= precision;
		else if (player->base.velocity.z < 0)
			player->base.velocity.z += precision;
	}
}