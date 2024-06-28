/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:02:46 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/28 18:55:04 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include <mlx.h>

bool	mouse_click_over(t_vars *vars, t_boxi box)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	return (x >= box.min.x && x <= box.max.x && y >= box.min.y
		&& y <= box.max.y && vars->buttons[1]);
}

void	menu_key(t_menu *menu, t_vars *vars, int c)
{
	(void) vars;
	if (menu->state == STATE_MULTIPLAYER)
	{
		text_edit_key(&menu->ip, c);
		text_edit_key(&menu->name, c);
	}
}

void menu_closed(t_vars *vars)
{
	r3d_raycast_world(&vars->r3d, &vars->map, vars);
	draw_gun(&vars->map.player->gun[vars->map.player->gun_index], &vars->r3d);
	draw_crosshair(&vars->r3d, vars);
	minimap_draw(&vars->minimap, &vars->r3d, vars);
	print_health(vars);
}
