/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:01:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/01 14:21:29 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_vars *vars)
{
	t_player	*player;

	player = player_new(vars, &vars->map, next_entity_id(vars));
	vars->menu.state = STATE_MAIN;
	vars->menu_open = true;
	vars->map.player = player;
	// player->base.transform = vars->map.spawns[0];
	// player->spawn_transform = vars->map.spawns[0];
	player->base.transform = (t_transform){v3(0, 0, 0), v3(0, 0, 0)};
	map_add_entity(&vars->map, player);
}
