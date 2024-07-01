/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_packets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:54:07 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 11:39:19 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"
#include "libft.h"

void	netserv_move_player(t_server *server, t_packet_pos *p, t_vars *vars)
{
	t_remote_client	*client;
	int				i;
	t_v3			pos;
	t_v3			pos2;

	(void) vars;
	if (p->eid < 0 || p->eid >= 8 || !server->clients[p->eid].present)
	{
		ft_printf("Error\nInvalid packet received from client.\n");
		return ;
	}
	i = p->eid;
	client = &server->clients[p->eid];
	pos = client->entity->transform.position;
	client->entity->transform.position = p->pos;
	client->entity->transform.rotation = p->rot;
	pos2 = client->entity->transform.position;
	p->eid = client->entity->id;
	netserv_broadcast(server, p, sizeof(t_packet_pos), i);
	if (client->entity->type == ENTITY_FAKE_PLAYER
		&& (pos.x != pos2.x || pos.z != pos2.z))
		sprite_tick(fake_player_get_sprite((t_fake_player *) client->entity,
				vars));
}

void	netserv_handle_pulse(t_server *server, t_packet_pulse *pulse)
{
	t_remote_client	*client;

	if (pulse->unique_id < 0 || pulse->unique_id >= MAX_CLIENT
		|| !server->clients[pulse->unique_id].present)
		return ;
	client = &server->clients[pulse->unique_id];
	client->last_pulse = getms();
	netserv_send(server, pulse, sizeof(t_packet_pulse), pulse->unique_id);
}

void	netserv_player_hit(t_server *serv, t_packet_hit *hit, t_vars *vars)
{
	t_entity		*entity;
	t_fake_player	*fake_player;
	int				client_id;

	(void)serv;
	client_id = netserv_client_from_entity_id(serv, hit->source_id);
	entity = map_get_entity_by_id(&vars->map, hit->entity_id);
	if (entity && entity->type == ENTITY_FAKE_PLAYER)
	{
		fake_player = (t_fake_player *) entity;
		fake_player->health -= hit->damage_taken;
	}
	else if (entity && entity->type == ENTITY_PLAYER)
	{
		((t_player *) entity)->health -= hit->damage_taken;
	}
	fake_player = (t_fake_player *) map_get_entity_by_id(&vars->map,
			hit->source_id);
	if (fake_player && fake_player->base.type == ENTITY_FAKE_PLAYER)
	{
		fp_reset_shoot_anim(fake_player);
		fake_player->is_shooting = true;
	}
	netserv_broadcast(serv, hit, sizeof(t_packet_hit), client_id);
}

void	netserv_respawn_player(t_server *server, t_packet_respawn *p,
	t_vars *vars)
{
	int			i;
	t_entity	*entity;

	(void) vars;
	i = netserv_client_from_entity_id(server, p->entity_id);
	if (i == -1)
		return ;
	entity = map_get_entity_by_id(&vars->map, p->entity_id);
	if (!entity || entity->type != ENTITY_FAKE_PLAYER)
		return ;
	((t_fake_player *) entity)->health = MAX_HEALTH;
	((t_fake_player *) entity)->base.is_dead = false;
	netserv_broadcast(server, p, sizeof(t_packet_respawn), i);
}

void	netserv_sync_door_state(t_server *server, t_packet_door_state *p,
	t_vars *vars)
{
	(void) server;
	if (p->pos.x < 0 || p->pos.x >= vars->map.width || p->pos.y < 0
		|| p->pos.y >= vars->map.height)
		return ;
	if (p->state)
		vars->map.tiles[p->pos.x + p->pos.y * vars->map.width] = TILE_DOOR;
	else
		vars->map.tiles[p->pos.x + p->pos.y * vars->map.width] = TILE_DOOR_OPEN;
	netserv_broadcast_door_state(server, p->pos, p->state, -1);
}
