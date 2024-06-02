/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:52:52 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/02 16:17:32 by vopekdas         ###   ########.fr       */
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

t_box	box_from_velocity_x(t_entity *entity)
{
	const t_v3	vel = entity->velocity;
	t_box		box;

	box.min.x = entity->transform.position.x + vel.x - entity->width / 2;
	box.max.x = entity->transform.position.x + vel.x + entity->width / 2;
	box.min.y = entity->transform.position.y - entity->height / 2;
	box.max.y = entity->transform.position.y + entity->height / 2;
	box.min.z = entity->transform.position.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + entity->depth / 2;
	return (box);
}

t_box	box_from_velocity_y(t_entity *entity)
{
	const t_v3	vel = entity->velocity;
	t_box		box;

	box.min.x = entity->transform.position.x - entity->width / 2;
	box.max.x = entity->transform.position.x + entity->width / 2;
	box.min.y = entity->transform.position.y + vel.y - entity->height / 2;
	box.max.y = entity->transform.position.y + vel.y + entity->height / 2;
	box.min.z = entity->transform.position.z - entity->depth / 2;
	box.max.z = entity->transform.position.z + entity->depth / 2;
	return (box);
}

t_box	box_from_velocity_z(t_entity *entity)
{
	const t_v3	vel = entity->velocity;
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

bool	collide_with_wall(t_box player, t_map *map, int x, int y)
{
	int			t;
	t_box		tile_box;

	t = map->tiles[x + y * map->width];
	if (t == TILE_FULL)
	{
		tile_box = box_from_wall(x, y);
		printf(YELLOW"MAP X = %f %f\n"WHITE, tile_box.min.x, tile_box.max.x);
		printf(YELLOW"MAP Y = %f %f\n"WHITE, tile_box.min.y, tile_box.max.y);
		printf(YELLOW"MAP Z = %f %f\n"WHITE, tile_box.min.z, tile_box.max.z);
		printf(CYAN"PLAYER X = %f %f\n"WHITE, player.min.x, player.max.x);
		printf(CYAN"PLAYER Y = %f %f\n"WHITE, player.min.y, player.max.y);
		printf(CYAN"PLAYER Z = %f %f\n"WHITE, player.min.z, player.max.z);
		if (collide(player, tile_box))
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
				if (collide_with_wall(player, map, x, y))
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

	const bool	vx_positive = player->base.velocity.x > 0;
	const bool	vy_positive = player->base.velocity.y > 0;
	const bool	vz_positive = player->base.velocity.z > 0;

	float	vx;
	float	vy;
	float	vz;

	bool	collide;
	t_box player_box;

// COLLISION ON X AXIS
	vx = player->base.velocity.x;
	player_box = box_from_velocity_x(&player->base);
	collide = collide_with_map(player_box, map);
	while (((vx_positive && vx > 0) || (!vx_positive && vx < 0)) && collide)
	{
		printf(CYAN"COLLIDE X\n"WHITE);
		if (vx_positive)
			vx -= precision;
		else
			vx += precision;
	}
	if ((vx_positive && player->base.velocity.x < 0) || (!vx_positive && player->base.velocity.x > 0))
		vx = 0;
	player->base.velocity.x = vx;

// COLLISION ON Y AXIS
	vy = player->base.velocity.y;
	player_box = box_from_velocity_y(&player->base);
	collide = collide_with_map(player_box, map);
	while (((vy_positive && vy > 0) || (!vy_positive && vy < 0)) && collide)
	{
		printf(CYAN"COLLIDE Y\n"WHITE);
		if (vy_positive)
			vy -= precision;
		else
			vy += precision;
	}
	if ((vy_positive && player->base.velocity.y < 0) || (!vy_positive && player->base.velocity.y > 0))
		vy = 0;
	player->base.velocity.y = vy;

// COLLISION ON Z AXIS
	vz = player->base.velocity.z;
	player_box = box_from_velocity_z(&player->base);
	collide = collide_with_map(player_box, map);
	while (((vz_positive && vz > 0) || (!vz_positive && vz < 0)) && collide)
	{
		printf(CYAN"COLLIDE Z\n"WHITE);
		if (vz_positive)
			vz -= precision;
		else
			vz += precision;
	}
	if ((vz_positive && player->base.velocity.z < 0) || (!vz_positive && player->base.velocity.z > 0))
		vz = 0;
	player->base.velocity.z = vz;

}
