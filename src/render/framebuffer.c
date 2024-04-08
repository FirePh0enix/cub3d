/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:01:28 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 23:57:52 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_framebuffer	*create_fb(int width, int height)
{
	t_framebuffer	*fb;

	fb = ft_calloc(1, sizeof(t_framebuffer));
	fb->width = width;
	fb->height = height;
	fb->depth = malloc(sizeof(float) * width * height);
	fb->color = malloc(sizeof(t_color) * width * height);
	return (fb);
}

void	fb_clear_depth_buffer(t_framebuffer *fb)
{
	const int	size = fb->width * fb->height;
	int			i;

	i = 0;
	while (i < size)
	{
		fb->depth[i] = -INFINITY;
		i++;
	}
}

void	fb_clear_color_buffer(t_framebuffer *fb, t_color color)
{
	const int	size = fb->width * fb->height;
	int			i;

	i = 0;
	while (i < size)
	{
		fb->color[i] = color;
		i++;
	}
}
