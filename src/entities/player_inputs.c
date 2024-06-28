/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:36:30 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/28 15:08:14 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>

static void	shoot(t_player *player, t_vars *vars)
{
	t_packet_hit	p;
	t_entity		*entity;

	entity = raycast_entity(&vars->map, (t_transform){
			v3(player->camera->pos.x, 0, player->camera->pos.z),
			player->camera->rot}, 10.0, ENTITY_FAKE_PLAYER);
	player->gun[vars->map.player->gun_index].has_shoot = true;
	if (_BONUS && entity)
	{
		if (!vars->is_server)
			netclient_send_hit(&vars->client, entity, 1);
		else
		{
			((t_fake_player *) entity)->health -= 1;
			p.type = PACKET_HIT;
			p.damage_taken = 1;
			p.source_id = player->base.id;
			p.entity_id = entity->id;
			netserv_broadcast(&vars->server, &p, sizeof(t_packet_hit), -1);
		}
	}
	else if (_BONUS && !vars->is_server)
		netclient_send_hit(&vars->client, NULL, 1);
}

static void	toggle_door(t_player *p, t_vars *vars)
{
	t_v2i	d;

	d = raycast_door(&vars->map, (t_transform){v3(p->camera->pos.x, 0,
				p->camera->pos.z), p->camera->rot}, 3.0);
	if (d.x >= 0 && d.y >= 0 && p->base.map->tiles[d.x
			+ d.y * p->base.map->width] == TILE_DOOR_OPEN)
		p->base.map->tiles[d.x + d.y * p->base.map->width] = TILE_DOOR;
	else if (d.x >= 0 && d.y >= 0 && p->base.map->tiles[d.x
			+ d.y * p->base.map->width] == TILE_DOOR)
		p->base.map->tiles[d.x + d.y * p->base.map->width] = TILE_DOOR_OPEN;
	if (_BONUS && vars->is_server)
		netserv_broadcast_door_state(&vars->server, d,
			p->base.map->tiles[d.x + d.y
			* p->base.map->width] == TILE_DOOR, -1);
	else if (_BONUS)
		netclient_send_door_state(&vars->client, d,
			p->base.map->tiles[d.x + d.y
			* p->base.map->width] == TILE_DOOR);
	p->e_pressed = true;
}

static void	keyboard_inputs(t_vars *vars, t_player *p)
{
	const float	speed = 5.0;
	const t_v3	forward = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0,
						p->base.transform.rotation.y, 0)), v3(0, 0, -1.0)));
	const t_v3	left = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0,
						p->base.transform.rotation.y, 0)), v3(-1.0, 0, 0)));

	if (vars->keys[XK_w])
		p->base.velocity = v3_add(p->base.velocity, v3_scale(forward, speed));
	if (vars->keys[XK_s])
		p->base.velocity = v3_sub(p->base.velocity, v3_scale(forward, speed));
	if (vars->keys[XK_a])
		p->base.velocity = v3_add(p->base.velocity, v3_scale(left, speed));
	if (vars->keys[XK_d])
		p->base.velocity = v3_sub(p->base.velocity, v3_scale(left, speed));
}

void	player_handle_inputs(t_vars *vars, t_player *p)
{
	const float	rot_speed = 0.02;

	keyboard_inputs(vars, p);
	if (vars->buttons[1] && !p->gun[vars->map.player->gun_index].has_shoot)
		shoot(p, vars);
	if (vars->keys[XK_e] && !p->e_pressed)
		toggle_door(p, vars);
	else if (!vars->keys[XK_e])
		p->e_pressed = false;
	if (vars->keys[XK_Left])
		player_rotate_y(p, rot_speed);
	if (vars->keys[XK_Right])
		player_rotate_y(p, -rot_speed);
	mlx_mouse_move(vars->mlx, vars->win, 1280 / 2.0, 720 / 2.0);
}
