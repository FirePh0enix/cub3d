/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:59:42 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/07 20:39:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"

void	player_tick(t_r3d *r3d, t_player *player);
void	player_draw(t_r3d *r3d, t_player *player);

t_player	*player_new()
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->base.eid = EID_PLAYER;
	player->base.tick = (void *) player_tick;
	player->base.draw = (void *) player_draw;
	player->camera = ft_calloc(1, sizeof(t_camera));
	return (player);
}

void	player_tick(t_r3d *r3d, t_player *player)
{
	const t_v3	camera_offset = v3(0.0, 0.0, 0.0);

	player->camera->position = v3_add(player->base.transform.position,
		camera_offset);
}

void	player_draw(t_r3d *r3d, t_player *player)
{
}
