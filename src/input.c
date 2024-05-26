/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phoenix <phoenix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:14:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/27 00:26:47 by phoenix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math/v2i.h"
#include "render/render.h"
#include <X11/Xlib.h>

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
