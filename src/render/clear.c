/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:59:06 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 13:31:42 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	r3d_clear_depth_buffer(t_r3d *r3d)
{
	const int	size = r3d->width * r3d->height;
	int			i;

	i = 0;
	while (i < size)
	{
		r3d->depth_buffer[i] = INFINITY;
		i++;
	}
}

void	r3d_clear_color_buffer(t_r3d *r3d, t_color color)
{
	const int	size = r3d->width * r3d->height;
	int			i;

	i = 0;
	while (i < size)
	{
		r3d->color_buffer[i] = color;
		i++;
	}
}
