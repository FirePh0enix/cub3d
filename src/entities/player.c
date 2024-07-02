/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:50:03 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/02 10:57:22 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"

void	player_tick(t_vars *vars, t_player *player);
void	player_free(t_vars *vars, t_player *player);

t_player	*player_new(t_vars *vars, t_map *map, int id)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->base.type = ENTITY_PLAYER;
	player->base.id = id;
	player->base.tick = (void *) player_tick;
	player->base.free = (void *) player_free;
	player->base.transform = (t_transform){0};
	player->base.map = map;
	player->camera = ft_calloc(1, sizeof(t_camera));
	player->base.velocity = v3(0, 0, 0);
	player->base.height = 2.0;
	player->base.width = 0.3;
	player->base.depth = 0.3;
	player->camera->plane_x = 0.0;
	player->camera->plane_x = 0.85;
	player->camera->dir_x = 0;
	player->camera->dir_y = -1;
	player->health = MAX_HEALTH;
	player->gun[0] = vars->pistol;
	player->gun[1] = vars->shotgun;
	player->gun[2] = vars->minigun;
	return (player);
}

void	player_tick(t_vars *v, t_player *p)
{
	if (v->menu_open)
		return ;
	if (v->is_focused)
		player_handle_inputs(v, p);
	if (_BONUS && p->health <= 0 && v->is_server)
	{
		p->base.is_dead = true;
		netserv_broadcast_dead_player(&v->server, v->map.player->base.id, -1);
		v->menu_open = true;
		v->menu.state = STATE_DEAD;
		return ;
	}
	if (p->base.is_dead)
		return ;
	adjust_vel(p, &v->map, v->delta_sec);
	p->base.transform.position = v3_add(p->base.transform.position,
			v3_scale(p->base.velocity, v->delta_sec));
	p->base.velocity.x *= 0.5;
	p->base.velocity.z *= 0.5;
	p->camera->pos = p->base.transform.position;
	tick_gun(&p->gun[p->gun_index]);
	if (_BONUS && !v->is_server)
		netclient_send_pos(&v->client, p->base.transform);
	else if (_BONUS)
		netserv_broadcast_pos(&v->server, p, -1);
}

void	player_free(t_vars *vars, t_player *player)
{
	(void) vars;
	free(player->camera);
}

void	player_mouse_event(int x, int y, t_vars *vars)
{
	const float	x_speed = x - 1280 / 2.0;
	t_player	*player;

	(void) y;
	if (!vars->is_focused || vars->menu_open)
		return ;
	player = vars->map.player;
	player_rotate_y(player, -x_speed / 2400.0);
}

void	player_rotate_y(t_player *player, float rot_speed)
{
	const float	old_plane_x = player->camera->plane_x;
	const float	old_dir_x = player->camera->dir_x;

	player->camera->rot.y += rot_speed;
	player->base.transform.rotation.y = player->camera->rot.y;
	player->camera->plane_x = old_plane_x * cos(-rot_speed)
		- player->camera->plane_y * sin(-rot_speed);
	player->camera->plane_y = old_plane_x * sin(-rot_speed)
		+ player->camera->plane_y * cos(-rot_speed);
	player->camera->dir_x = old_dir_x * cos(-rot_speed)
		- player->camera->dir_y * sin(-rot_speed);
	player->camera->dir_y = old_dir_x * sin(-rot_speed)
		+ player->camera->dir_y * cos(-rot_speed);
}
