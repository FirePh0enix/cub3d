/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:59:42 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/22 13:50:11 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"

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
	player->camera->rotation = v3(0.0, 0.0, 0.0);
	player->camera->position = v3_add(player->base.transform.position,
		camera_offset);
}

void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera)
{
}
