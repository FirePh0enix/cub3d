/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_velocity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:59:27 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/26 14:04:46 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	collide_x(t_player *player, t_map *map, float delta)
{
	const float	precision = 0.01;

	while (player->base.velocity.x < -0.02 || player->base.velocity.x > 0.02)
	{
		if (!collide_map(box_from_velocity_x(&player->base, delta), map))
			break ;
		if (player->base.velocity.x > 0)
			player->base.velocity.x -= precision;
		else
			player->base.velocity.x += precision;
	}
	if (player->base.velocity.x >= -EPSILON
		&& player->base.velocity.x <= EPSILON)
		player->base.velocity.x = 0;
}

static void	collide_y(t_player *player, t_map *map, float delta)
{
	const float	precision = 0.01;

	while (player->base.velocity.y < -0.02 || player->base.velocity.y > 0.02)
	{
		if (!collide_map(box_from_velocity_y(&player->base, delta), map))
			break ;
		if (player->base.velocity.y > 0)
			player->base.velocity.y -= precision;
		else
			player->base.velocity.y += precision;
	}
	if (player->base.velocity.y >= -EPSILON
		&& player->base.velocity.y <= EPSILON)
		player->base.velocity.y = 0;
}

static void	collide_z(t_player *player, t_map *map, float delta)
{
	const float	precision = 0.01;

	while (player->base.velocity.z < -0.02 || player->base.velocity.z > 0.02)
	{
		if (!collide_map(box_from_velocity_z(&player->base, delta), map))
			break ;
		if (player->base.velocity.z > 0)
			player->base.velocity.z -= precision;
		else
			player->base.velocity.z += precision;
	}
	if (player->base.velocity.z >= -EPSILON
		&& player->base.velocity.z <= EPSILON)
		player->base.velocity.z = 0.0;
}

void	adjust_vel(t_player *player, t_map *map, float delta)
{
	collide_x(player, map, delta);
	collide_y(player, map, delta);
	collide_z(player, map, delta);
}
