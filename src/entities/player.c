/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phoenix <phoenix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:59:42 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/27 00:26:40 by phoenix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"
#include "mlx.h"
#include "../math/utils.h"
#include <stdio.h>

void	player_tick(t_vars *vars, t_player *player);
void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera, t_vars *vars);

t_player	*player_new(t_vars *vars, t_scene *scene)
{
	t_player	*player;

	(void) vars;
	player = ft_calloc(1, sizeof(t_player));
	player->base.eid = EID_PLAYER;
	player->base.tick = (void *) player_tick;
	player->base.draw = (void *) player_draw;
	player->base.transform = (t_transform){};
	player->base.scene = scene;
	player->camera = ft_calloc(1, sizeof(t_camera));
	return (player);
}

void	player_tick(t_vars *vars, t_player *player)
{
	const t_v3	camera_offset = v3(0.0, 0.0, 0.0);
	const t_v3	forward = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0, player->base.transform.rotation.y, 0)), v3(0, 0, -1.0)));
	const t_v3	left = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0, player->base.transform.rotation.y, 0)), v3(-1.0, 0, 0)));
	const float	speed = 5.0;
	t_v3		velocity;

	velocity = v3(0, 0, 0);
	if (vars->keys[XK_w])
		velocity = v3_add(velocity, v3_scale(forward, speed));
	if (vars->keys[XK_s])
		velocity = v3_sub(velocity, v3_scale(forward, speed));
	if (vars->keys[XK_a])
		velocity = v3_add(velocity, v3_scale(left, speed));
	if (vars->keys[XK_d])
		velocity = v3_sub(velocity, v3_scale(left, speed));
	player->base.transform.position = v3_add(player->base.transform.position, v3_scale(velocity, vars->delta_sec));
	player->camera->position = v3_add(player->base.transform.position,
		camera_offset);

	mlx_mouse_move(vars->mlx, vars->win, 1280 / 2.0, 720 / 2.0);
}

void	player_mouse_event(int x, int y, t_vars *vars)
{
	const float x_speed = x - 1280 / 2.0;
	const float y_speed = y - 720 / 2.0;
	t_player	*player;

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
