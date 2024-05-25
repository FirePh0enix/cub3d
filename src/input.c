/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:14:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/14 13:18:35 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render/render.h"
#include <stdio.h>

int	key_pressed_hook(int keycode, t_vars *vars)
{
	if (keycode < 0 || keycode >= 0xFFFF)
		return (0);
	r3d_key_hook(keycode, vars->r3d);
	vars->keys[keycode] = true;
	return (0);
}

int	key_released_hook(int keycode, t_vars *vars)
{
	if (keycode < 0 || keycode >= 0xFFFF)
		return (0);
	vars->keys[keycode] = false;
	return (0);
}

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	vars->mouse_pos = (t_v2i){x, y};
	return (0);
}
