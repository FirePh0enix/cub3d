/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:01:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/11 23:59:26 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	init_player(t_vars *vars)
{
	t_player	*player;

	player = player_new(vars, &vars->map, next_entity_id(vars));
	if (!player)
		return (false);
	vars->menu.state = STATE_MAIN;
	vars->menu_open = true;
	vars->map.player = player;
	player->base.transform = vars->map.spawns[0];
	player->spawn_transform = vars->map.spawns[0];
	player_rotate_y(player, player->base.transform.rotation.y);
	map_add_entity(&vars->map, player);
	return (true);
}
