/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:59:06 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 16:06:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	r3d_clear_depth_buffer(t_r3d *r3d)
{
	fb_clear_depth_buffer(r3d->fb);
}

void	r3d_clear_color_buffer(t_r3d *r3d, t_color color)
{
	fb_clear_color_buffer(r3d->fb, color);
}
