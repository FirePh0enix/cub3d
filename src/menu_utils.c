/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:02:46 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/28 15:03:17 by ledelbec         ###   ########.fr       */
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
