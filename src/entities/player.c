/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:59:42 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/14 15:48:41 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"
#include "mlx.h"
#include <stdio.h>

void	player_tick(t_vars *vars, t_player *player);
void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera);

t_player	*player_new(t_vars *vars, t_scene *scene)
{
	t_player	*player;

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

	if (vars->keys[XK_w])
		player->base.transform.position.z += -0.1;
	if (vars->keys[XK_s])
		player->base.transform.position.z += 0.1;
	if (vars->keys[XK_a])
		player->base.transform.position.x += -0.1;
	if (vars->keys[XK_d])
		player->base.transform.position.x += 0.1;
	// player->camera->rotation = v3(0.0, 0.0, 0.0);
	player->camera->position = v3_add(player->base.transform.position,
		camera_offset);

	// Get the relative position of the mouse
	int x, y;
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);

	//int x2 = player->mouse_x - x;
	//int y2 = player->mouse_y - y;

	player->mouse_x = x;
	player->mouse_y = y;

	float x_speed = x - 1280 / 2.0;
	float y_speed = y - 720 / 2.0;

	printf("Relative: x = %f, y = %f\n", x_speed, y_speed);

	player->camera->rotation.y += x_speed / 100.0;
	player->camera->rotation.x += y_speed / 100.0;

	// mlx_mouse_move(vars->mlx, vars->win, 1280 / 2, 720 / 2);
}

void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera)
{
	(void) r3d;
	(void) player;
	(void) camera;
}
