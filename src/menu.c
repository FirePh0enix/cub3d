/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:03:54 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/12 11:13:56 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"

void	menu_draw(t_menu *menu, t_r3d *r3d)
{
	button_draw(&menu->singleplayer, r3d);
}

void	menu_tick(t_menu *menu, t_vars *vars)
{
	button_tick(&menu->singleplayer, vars);
}
