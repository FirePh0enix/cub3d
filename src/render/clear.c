/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:59:06 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/18 18:56:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	r3d_clear_depth_buffer(t_r3d *r3d)
{
	int	i;

	i = 0;
	while (i < r3d->width * r3d->height)
	{
		r3d->depth_buffer[i] = INFINITY; //-INFINITY;
		i++;
	}
}

void	r3d_clear_color_buffer(t_r3d *r3d, t_color color)
{
	int	i;

	i = 0;
	while (i < r3d->width * r3d->height)
	{
		r3d->color_buffer[i] = color;
		i++;
	}
}
