/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:03:54 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/28 12:04:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include "mlx.h"
#include "network/net.h"
#include "render/render.h"
#include "scene.h"

bool	mouse_click_over(t_vars *vars, t_boxi box)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	return (x >= box.min.x && x <= box.max.x && y >= box.min.y
		&& y <= box.max.y && vars->buttons[1]);
}

void	menu_draw(t_menu *menu, t_r3d *r3d, t_vars *vars)
{
	if (menu->state == STATE_MAIN)
	{
		button_draw(&menu->singleplayer, r3d);
		button_draw(&menu->multiplayer, r3d);
	}
	else if (menu->state == STATE_MULTIPLAYER)
	{
		button_draw(&menu->host, r3d);
		button_draw(&menu->join, r3d);
		img_draw(&menu->ip_img, r3d);
		text_edit_draw(&menu->ip, r3d, vars);
		img_draw(&menu->name_img, r3d);
		text_edit_draw(&menu->name, r3d, vars);
	}
	else if (menu->state == STATE_DEAD)
	{
		button_draw(&menu->dead_msg, r3d);
		button_draw(&menu->respawn, r3d);
	}
}

static void	menu_tick_multi(t_menu *menu, t_vars *vars)
{
	button_tick(&menu->host, vars);
	button_tick(&menu->join, vars);
	text_edit_tick(&menu->ip, vars);
	text_edit_tick(&menu->name, vars);
	if (mouse_click_over(vars, menu->ip.box))
	{
		menu->ip.focused = true;
		menu->name.focused = false;
	}
	else if (mouse_click_over(vars, menu->name.box))
	{
		menu->ip.focused = false;
		menu->name.focused = true;
	}
}

void	menu_tick(t_menu *menu, t_vars *vars)
{
	if (menu->state == STATE_MAIN)
	{
		button_tick(&menu->singleplayer, vars);
		button_tick(&menu->multiplayer, vars);
	}
	else if (menu->state == STATE_MULTIPLAYER)
	{
		menu_tick_multi(menu, vars);
	}
	else if (menu->state == STATE_DEAD)
	{
		button_tick(&menu->respawn, vars);
	}
	if (!vars->buttons[1])
		menu->already_pressed = false;
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
