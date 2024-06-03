/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:52:52 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/03 13:56:56 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math/v3.h"
#include "render/render.h"
#include "scene.h"
#include <X11/Xlib.h>
#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

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

t_box	box_from_velocity_x(t_entity *entity, float delta)
{
	const t_v3	vel = v3_scale(entity->velocity, delta);
	t_box		box;

	box.min.x = entity->transform.position.x + vel.x - entity->width / 2;
	box.max.x = entity->transform.position.x + vel.x + entity->width / 2;
	box.min.y = entity->transform.position.y - entity->height / 2;
	box.max.y = entity->transform.position.y + entity->height / 2;
	box.min.z = entity->transform.position.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + entity->depth / 2;
	return (box);
}

t_box	box_from_velocity_y(t_entity *entity, float delta)
{
	const t_v3	vel = v3_scale(entity->velocity, delta);
	t_box		box;

	box.min.x = entity->transform.position.x - entity->width / 2;
	box.max.x = entity->transform.position.x + entity->width / 2;
	box.min.y = entity->transform.position.y + vel.y - entity->height / 2;
	box.max.y = entity->transform.position.y + vel.y + entity->height / 2;
	box.min.z = entity->transform.position.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + entity->depth / 2;
	return (box);
}

t_box	box_from_velocity_z(t_entity *entity, float delta)
{
	const t_v3	vel = v3_scale(entity->velocity, delta);
	t_box		box;

	box.min.x = entity->transform.position.x - entity->width;
	box.max.x = entity->transform.position.x + entity->width;
	box.min.y = entity->transform.position.y - entity->height;
	box.max.y = entity->transform.position.y + entity->height;
	box.min.z = entity->transform.position.z + vel.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + vel.z + entity->depth / 2;
	return (box);
}

t_box	box_from_wall(int x, int y)
{
	t_box	box;

	box.min.x = x * WALL_SIZE - WALL_SIZE / 2;
	box.max.x = x * WALL_SIZE + WALL_SIZE / 2;
	box.min.y = WALL_SIZE / 2 - WALL_SIZE / 2;
	box.max.y = WALL_SIZE / 2 + WALL_SIZE / 2;
	box.min.z = y * WALL_SIZE - WALL_SIZE / 2;
	box.max.z = y * WALL_SIZE + WALL_SIZE / 2;
	return (box);
}

bool	collide_with_wall(t_box player, int x, int y)
{
	t_box		tile_box;

	tile_box = box_from_wall(x, y);

	if (collide(player, tile_box))
	{
		return (true);
	}
	return (false);
}

bool collide_with_map(t_box player, t_map *map)
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
				if (collide_with_wall(player, x, y))
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

void	adjust_player_pos(t_player *player, t_map *map, float delta)
{
	const float	precision = 0.01;


#define EPSILON 1e-1

// COLLISION ON X AXIS
	while (player->base.velocity.x < -0.02 || player->base.velocity.x > 0.02)
	{
		if (!collide_with_map(box_from_velocity_x(&player->base, delta), map))
			break ;
		if (player->base.velocity.x > 0)
			player->base.velocity.x -= precision;
		else
			player->base.velocity.x += precision;
	}
	if (player->base.velocity.x >= -EPSILON && player->base.velocity.x <= EPSILON)
		player->base.velocity.x = 0;

	while (player->base.velocity.y < -0.02 || player->base.velocity.y > 0.02)
	{
		if (!collide_with_map(box_from_velocity_y(&player->base, delta), map))
			break ;
		if (player->base.velocity.y > 0)
			player->base.velocity.y -= precision;
		else
			player->base.velocity.y += precision;
	}
	if (player->base.velocity.y >= -EPSILON && player->base.velocity.y <= EPSILON)
		player->base.velocity.y = 0;

	while (player->base.velocity.z < -0.02 || player->base.velocity.z > 0.02)
	{
		if (!collide_with_map(box_from_velocity_z(&player->base, delta), map))
			break ;
		if (player->base.velocity.z > 0)
			player->base.velocity.z -= precision;
		else
			player->base.velocity.z += precision;
	}
	if (player->base.velocity.z >= -EPSILON && player->base.velocity.z <= EPSILON)
		player->base.velocity.z = 0;

}
