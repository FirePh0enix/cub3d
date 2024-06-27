/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_packets2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:26:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 22:27:29 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"

void	netclient_del_entity(t_client *client, t_vars *vars,
	t_packet_del_entity *p)
{
	t_entity	*entity;

	(void) client;
	entity = map_get_entity_by_id(&vars->map, p->entity_id);
	if (entity == NULL)
		return ;
	map_remove_entity(&vars->map, entity);
}

void	netclient_dead(t_client *client, t_vars *vars,
	t_packet_dead *p)
{
	t_entity	*entity;

	(void) client;
	entity = map_get_entity_by_id(&vars->map, p->entity_id);
	if (entity == NULL)
		return ;
	entity->is_dead = true;
	if (entity->type == ENTITY_PLAYER)
	{
		vars->menu_open = true;
		vars->menu.state = STATE_DEAD;
	}
}

void	netclient_respawn(t_client *client, t_vars *vars,
	t_packet_respawn *p)
{
	t_entity	*entity;

	(void) client;
	entity = map_get_entity_by_id(&vars->map, p->entity_id);
	if (entity == NULL)
		return ;
	entity->is_dead = false;
	if (entity->type == ENTITY_PLAYER)
		((t_player *) entity)->health = MAX_HEALTH;
	else if (entity->type == ENTITY_FAKE_PLAYER)
		((t_fake_player *) entity)->health = MAX_HEALTH;
}

void	netclient_hit(t_client *client, t_vars *vars, t_packet_hit *p)
{
	t_entity	*entity;

	(void) client;
	entity = map_get_entity_by_id(&vars->map, p->source_id);
	if (entity && entity->type == ENTITY_FAKE_PLAYER)
	{
		fp_reset_shoot_anim((t_fake_player *) entity);
		((t_fake_player *) entity)->is_shooting = true;
	}
	entity = map_get_entity_by_id(&vars->map, p->entity_id);
	if (entity && entity->type == ENTITY_PLAYER)
		((t_player *) entity)->health -= p->damage_taken;
}

void	netclient_door_state(t_client *client, t_vars *vars,
	t_packet_door_state *p)
{
	(void) client;
	if (p->pos.x < 0 || p->pos.x >= vars->map.width || p->pos.y < 0
		|| p->pos.y >= vars->map.height)
		return ;
	if (p->state)
		vars->map.tiles[p->pos.x + p->pos.y * vars->map.width] = TILE_DOOR;
	else
		vars->map.tiles[p->pos.x + p->pos.y * vars->map.width] = TILE_DOOR_OPEN;
}
