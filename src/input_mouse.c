/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:54:01 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/26 15:00:03 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	mouse_scroll(t_vars *vars)
{
	int	gun_index;

	gun_index = vars->map.player->gun_index;
	if (vars->buttons[MOUSE_SCROLL_UP])
	{
		vars->map.player->gun_index++;
		if (vars->map.player->gun_index >= GUN_MAX)
			vars->map.player->gun_index = 0;
		vars->map.player->gun[gun_index].main_anim.current_frame = 0;
		vars->map.player->gun[gun_index].main_anim.last_frame_tick = getms();
		vars->map.player->gun[gun_index].has_shoot = false;
		vars->map.player->gun[gun_index].reloading = false;
	}
	if (vars->buttons[MOUSE_SCROLL_DOWN])
	{
		vars->map.player->gun_index--;
		if (vars->map.player->gun_index < 0)
			vars->map.player->gun_index = GUN_MAX - 1;
		vars->map.player->gun[gun_index].main_anim.current_frame = 0;
		vars->map.player->gun[gun_index].main_anim.last_frame_tick = getms();
		vars->map.player->gun[gun_index].has_shoot = false;
		vars->map.player->gun[gun_index].reloading = false;
	}
	return (0);
}
