/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:59:42 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/05 13:35:58 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"
#include "mlx.h"
#include "../math/utils.h"
#include <stdio.h>

void	player_tick(t_vars *vars, t_player *player);
void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera, t_vars *vars);

t_player	*player_new(t_vars *vars, t_scene *scene, int id)
{
	t_player	*player;

	(void) vars;
	player = ft_calloc(1, sizeof(t_player));
	player->base.type = ENTITY_PLAYER;
	player->base.id = id;
	player->base.tick = (void *) player_tick;
	player->base.draw = (void *) player_draw;
	player->base.transform = (t_transform){};
	player->base.scene = scene;
	player->camera = ft_calloc(1, sizeof(t_camera));
	player->base.velocity = v3(0, 0, 0);
	player->base.height = 3.0;
	player->base.width = 0.5;
	player->base.depth = 1.0;
	return (player);
}

static bool	is_on_ground(t_player *player)
{
	return (player->base.transform.position.y == 0);
}

void	player_tick(t_vars *vars, t_player *player)
{
	const t_v3	camera_offset = v3(0.0, 1.6, 0.0);
	const t_v3	forward = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0, player->base.transform.rotation.y, 0)), v3(0, 0, -1.0)));
	const t_v3	left = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0, player->base.transform.rotation.y, 0)), v3(-1.0, 0, 0)));
	const float	speed = 15.0;
	const float	jump_force = 20.0;

	if (!vars->is_focused)
		return ;
	if (vars->keys[XK_w])
		player->base.velocity = v3_add(player->base.velocity, v3_scale(forward, speed));
	if (vars->keys[XK_s])
		player->base.velocity = v3_sub(player->base.velocity, v3_scale(forward, speed));
	if (vars->keys[XK_a])
		player->base.velocity = v3_add(player->base.velocity, v3_scale(left, speed));
	if (vars->keys[XK_d])
		player->base.velocity = v3_sub(player->base.velocity, v3_scale(left, speed));

	if (vars->keys[XK_space] && !player->has_jump && is_on_ground(player))
	{
		player->base.velocity.y += jump_force;
		player->has_jump = true;
	}
	else if (!vars->keys[XK_space] && is_on_ground(player))
		player->has_jump = false;

	player->base.velocity.y -= 0.8;

	adjust_player_pos(player, vars->map, vars->delta_sec, vars->scene->entities);

	player->base.transform.position = v3_add(player->base.transform.position, v3_scale(player->base.velocity, vars->delta_sec));

	if (player->base.transform.position.y < 0)
	{
		player->base.transform.position.y = 0;
		player->base.velocity.y = 0;
	}

	player->camera->position = v3_add(player->base.transform.position,
		camera_offset);

	player->base.velocity.x *= 0.5;
	player->base.velocity.z *= 0.5;

	//
	// Interactions
	//

	if (vars->keys[XK_e] && !player->has_open_door)
	{
		t_door *entity = (void *) raycast_entity(vars->scene, (t_transform){player->camera->position, player->camera->rotation}, 3.0, ENTITY_DOOR);
		if (entity != NULL)
		{
			if (entity->target_angle == 90.0)
				entity->target_angle = 0.0;
			else
				entity->target_angle = 90.0;
		}
		player->has_open_door = true;
	}
	else if (!vars->keys[XK_e])
		player->has_open_door = false;

	mlx_mouse_move(vars->mlx, vars->win, 1280 / 2.0, 720 / 2.0);

	if (!vars->is_server)
		netclient_send_pos(&vars->client, player->base.transform);
	else
		netserv_broadcast_pos(&vars->server, player, -1);
}

void	player_mouse_event(int x, int y, t_vars *vars)
{
	const float x_speed = x - 1280 / 2.0;
	const float y_speed = y - 720 / 2.0;
	t_player	*player;

	if (!vars->is_focused)
		return ;
	player = vars->scene->player;

	player->camera->rotation.x -= y_speed / 1200.0;
	player->camera->rotation.x = clampf(player->camera->rotation.x, -M_PI / 2, M_PI / 2);

	player->camera->rotation.y -= x_speed / 1200.0;
	player->base.transform.rotation.y = player->camera->rotation.y;
}

void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera, t_vars *vars)
{
	(void) r3d;
	(void) player;
	(void) camera;
	(void) vars;
}
