/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:52:52 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/05 13:59:24 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "math/v3.h"
#include "render/render.h"
#include "scene.h"
#include <X11/Xlib.h>
#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

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

	box.min.x = entity->transform.position.x - entity->width / 2;
	box.max.x = entity->transform.position.x + entity->width / 2;
	box.min.y = entity->transform.position.y - entity->height / 2;
	box.max.y = entity->transform.position.y + entity->height / 2;
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

	if (collide_aabb_vs_aabb(player, tile_box))
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

bool collide_with_entities(t_entity **entities, t_box player)
{
	int		i;
	int		size;
	t_box	entity_box;

	i = 0;
	size = ft_vector_size(entities);
	while (i < size)
	{
		if (entities[i]->type == ENTITY_DOOR)
		{
			entity_box = box_from_entity(entities[i]);
			if (collide_aabb_vs_aabb(player, entity_box))
			{
				printf("ENTITY MIN: %f %f %f\n", entity_box.min.x, entity_box.min.y, entity_box.min.z);
				printf("ENTITY MAX: %f %f %f\n", entity_box.max.x, entity_box.max.y, entity_box.max.z);
				printf("PLAYER MIN: %f %f %f\n", player.min.x, player.min.y, player.min.z);
				printf("PLAYER MAX: %f %f %f\n", player.max.x, player.max.y, player.max.z);
				printf("----------------------------------------------\n");
					return (true);
			}
		}
		++i;
	}
	return (false);
}

void	adjust_player_pos(t_player *player, t_map *map, float delta, t_entity **entities)
{
	const float	precision = 0.01;

	while (player->base.velocity.x < -0.02 || player->base.velocity.x > 0.02)
	{
		if (!collide_with_map(box_from_velocity_x(&player->base, delta), map) && !collide_with_entities(entities, box_from_velocity_x(&player->base, delta)))
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
		if (!collide_with_entities(entities, box_from_velocity_y(&player->base, delta)) && !collide_with_entities(entities, box_from_velocity_y(&player->base, delta)))
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
		if (!collide_with_map(box_from_velocity_z(&player->base, delta), map) && !collide_with_entities(entities, box_from_velocity_z(&player->base, delta)))
			break ;
		if (player->base.velocity.z > 0)
			player->base.velocity.z -= precision;
		else
			player->base.velocity.z += precision;
	}
	if (player->base.velocity.z >= -EPSILON && player->base.velocity.z <= EPSILON)
		player->base.velocity.z = 0.0;

}
