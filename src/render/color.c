/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:20:58 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/05 13:46:20 by ledelbec         ###   ########.fr       */
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
