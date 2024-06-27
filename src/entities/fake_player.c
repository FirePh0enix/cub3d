/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:50:40 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/27 17:33:31 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"
#include <stdio.h>

void	fake_player_tick(t_vars *vars, t_fake_player *fp)
{
	t_sprite	*sp;

	(void) vars;
	if (fp->health <= 0 && vars->is_server)
	{
		fp->base.is_dead = true;
		netserv_broadcast_dead_player(&vars->server, fp->base.id, -1);
	}
	if (fp->is_shooting)
	{
		sp = fake_player_get_sprite(fp, vars);
		sprite_tick(sp);
		if (sprite_is_end(sp))
			fp->is_shooting = false;
	}
	else
	{
		sp = fake_player_get_sprite(fp, vars);
		sprite_tick(sp);
	}
}

t_fake_player	*fake_player_new(t_vars *vars, t_map *map, int id, t_skin skin)
{
	t_fake_player	*fp;

	(void) vars;
	fp = ft_calloc(1, sizeof(t_fake_player));
	fp->base.type = ENTITY_FAKE_PLAYER;
	fp->base.id = id;
	fp->base.tick = (void *) fake_player_tick;
	fp->base.transform = (t_transform){0};
	fp->base.map = map;
	fp->base.velocity = v3(0, 0, 0);
	fp->base.height = 1.0;
	fp->base.width = 0.7;
	fp->base.depth = 0.7;
	fp->health = MAX_HEALTH;
	fp->skin = skin;
	ft_memcpy(fp->sp, vars->skin[skin], sizeof(t_sprite[8]));
	ft_memcpy(fp->sh, vars->skin_shoot[skin], sizeof(t_sprite[8]));
	return (fp);
}

t_image	*fake_player_get_image(t_fake_player *fp, t_vars *vars)
{
	return (sprite_get_image(fake_player_get_sprite(fp, vars)));
}
