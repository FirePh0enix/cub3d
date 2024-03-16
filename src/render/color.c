/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:20:58 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/16 11:13:20 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	hex(unsigned int hex)
{
	return ((t_color){hex});
}

t_color	rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.t = t;
	return (c);
}

t_color	rgbaf(float r, float g, float b, float t)
{
	t_color	c;

	c.r = r * 255;
	c.g = g * 255;
	c.b = b * 255;
	c.t = t * 255;
	return (c);
}

t_color	grayscalef(float f)
{
	return (rgba(f * 255, f * 255, f * 255, 1.0));
}

t_color	color_scale(t_color col, float f)
{
	col.r *= f;
	col.g *= f;
	col.b *= f;
	return (col);
}
