/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_packets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:51:48 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/11 23:44:16 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"

void	netclient_packet_response(t_client *client, t_vars *vars,
	t_packet_connect_response *p)
{
	ft_printf("info : response received from the server!\n");
	client->unique_id = p->unique_id;
	client->entity_id = p->entity_id;
	vars->map.player->base.id = client->entity_id;
	vars->map.player->spawn_transform = vars->map.spawns[
		(p->unique_id + 1) % vars->map.spawn_count];
	vars->map.player->base.transform = vars->map.player->spawn_transform;
	client->last_pulse = getms();
	vars->menu_open = false;
}

void	netclient_deny(t_client *client, t_vars *vars,
	t_packet_deny *p)
{
	(void) client;
	if (p->reason != REASON_INVALID_MAP)
		ft_printf("error: Connection denied: %s\n", reason_str(p->reason));
	else
		ft_printf("error: Connection denied: Invalid map, `%s` was expected but"
			"`%s` was loaded\n",
			p->map, vars->map.name);
}

void	netclient_packet_pos(t_client *client, t_vars *vars,
	t_packet_pos *p)
{
	t_entity	*entity;
	t_v3		pos;
	t_v3		pos2;

	(void) client;
	entity = map_get_entity_by_id(&vars->map, p->eid);
	if (entity != NULL)
	{
		pos = entity->transform.position;
		entity->transform.position = p->pos;
		entity->transform.rotation = p->rot;
		pos2 = entity->transform.position;
		if (entity->type == ENTITY_FAKE_PLAYER && (pos.x != pos2.x
				|| pos.z != pos2.z))
			sprite_tick(fake_player_get_sprite((t_fake_player *) entity, vars));
	}
}

static t_entity	*new_entity(t_packet_new_entity *p, t_vars *vars)
{
	t_entity	*entity;

	entity = NULL;
	if (p->entity_type == ENTITY_FAKE_PLAYER)
		entity = (void *) fake_player_new(vars, &vars->map, p->entity_id,
				p->skin);
	return (entity);
}

void	netclient_new_entity(t_client *client, t_vars *vars,
	t_packet_new_entity *p)
{
	t_entity	*entity;

	(void) client;
	entity = new_entity(p, vars);
	if (!entity)
		return ;
	map_add_entity(&vars->map, entity);
}
