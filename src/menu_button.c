/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:04:29 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 22:26:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include "mlx.h"
#include "render/render.h"

void	button_draw(t_button *button, t_r3d *r3d)
{
	sprite_draw_single(r3d, button->image, (t_v2i){
		button->box.min.x, button->box.min.y,
	}, button->scale);
}

void	button_tick(t_button *button, t_vars *vars)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	if (x >= button->box.min.x && x <= button->box.max.x
		&& y >= button->box.min.y
		&& y <= button->box.max.y && vars->buttons[1]
		&& button->pressed && !vars->menu.already_pressed)
	{
		button->pressed(vars);
		vars->menu.already_pressed = true;
	}
}
