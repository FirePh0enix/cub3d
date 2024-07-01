/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:03:54 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 11:22:54 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include "network/net.h"
#include "render/render.h"
#include "scene.h"

#if _BONUS == 1

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

#else

void	menu_draw(t_menu *menu, t_r3d *r3d, t_vars *vars)
{
	(void) vars;
	if (menu->state == STATE_MAIN)
	{
		button_draw(&menu->singleplayer, r3d);
	}
	else if (menu->state == STATE_DEAD)
	{
		button_draw(&menu->dead_msg, r3d);
		button_draw(&menu->respawn, r3d);
	}
}

#endif

#if _BONUS == 1

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

#else

void	menu_tick(t_menu *menu, t_vars *vars)
{
	if (menu->state == STATE_MAIN)
	{
		button_tick(&menu->singleplayer, vars);
	}
	else if (menu->state == STATE_DEAD)
	{
		button_tick(&menu->respawn, vars);
	}
	if (!vars->buttons[1])
		menu->already_pressed = false;
}

#endif
