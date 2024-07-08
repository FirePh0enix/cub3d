/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:35:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/08 16:13:59 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"

void	singleplayer_pressed(t_vars *vars)
{
	vars->menu_open = false;
	vars->is_server = true;
	if (_BONUS)
		netserv_init(&vars->server, vars, SERVER_PORT);
	map_reset(&vars->map);
}

void	multiplayer_pressed(t_vars *vars)
{
	vars->menu.state = STATE_MULTIPLAYER;
}

void	host_pressed(t_vars *vars)
{
	save_data(&vars->menu);
	vars->is_server = true;
	if (_BONUS)
		netserv_init(&vars->server, vars, SERVER_PORT);
	vars->menu_open = false;
	map_reset(&vars->map);
}

void	join_pressed(t_vars *vars)
{
	save_data(&vars->menu);
	vars->is_server = false;
	if (_BONUS)
	{
		netclient_init(&vars->client, vars->menu.ip.buffer, SERVER_PORT);
		netclient_connect(&vars->client, vars->menu.name.buffer, vars);
	}
	map_reset(&vars->map);
}

void	respawn_pressed(t_vars *vars)
{
	if (_BONUS && vars->is_server)
		netserv_broadcast_respawn(&vars->server, vars->server.player_id, -1);
	else if (_BONUS)
		netclient_send_respawn(&vars->client);
	vars->menu_open = false;
	vars->map.player->base.transform = vars->map.player->spawn_transform;
	vars->map.player->base.is_dead = false;
	vars->map.player->health = MAX_HEALTH;
}
