/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:59:06 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/05 15:16:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdio.h>
#include "../cub3d.h"

void	r3d_clear_depth_buffer(t_r3d *r3d)
{
	fb_clear_depth_buffer(r3d->fb);
}

void	r3d_clear_color_buffer(t_r3d *r3d, t_color color)
{
	fb_clear_color_buffer(r3d->fb, color);
}

void	r3d_draw_floor_ceil(t_r3d *r3d, t_map *map)
{
	(void) r3d;
	(void) map;
}
