/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:04:21 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/22 00:38:49 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_v2i	screen_coords(t_r3d *r3d, t_v2 v)
{
	t_v2i	ov;

	ov.x = (1 + v.x) * 0.5 * r3d->width;
	ov.y = (1 + v.y) * 0.5 * r3d->height;
	return (ov);
}

static void	draw_glyph(t_r3d *r3d, t_font *font, char c, t_v2i pos)
{
	const int	off = font_x_offset(font, c);
	int			x;
	int			y;
	t_color		col;

	x = 0;
	while (x < font->x_size)
	{
		y = 0;
		while (y < font->y_size)
		{
			col = ((t_color *)font->ppm->data)[off + x + y * font->ppm->width];
			r3d->color_buffer[(pos.x + x) + (pos.y + y) * r3d->width] = col;
			y++;
		}
		x++;
	}
}

void	r3d_draw_text(t_r3d *r3d, t_font *font, char *text, t_v2 pos)
{
	const size_t	size = ft_strlen(text);
	t_v2i		spos;
	size_t			i;

	spos = screen_coords(r3d, pos);
	i = 0;
	while (i < size)
	{
		draw_glyph(r3d, font, text[i], spos);
		i++;
		spos.x += font->x_size;
	}
}
