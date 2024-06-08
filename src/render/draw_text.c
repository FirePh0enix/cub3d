/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:04:21 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 13:32:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"

static t_v2i	screen_coords(t_r3d *r3d, t_v2 v)
{
	t_v2i	ov;

	ov.x = (1 + v.x) * 0.5 * r3d->width;
	ov.y = (1 + v.y) * 0.5 * r3d->height;
	return (ov);
}

static float	to_ndc_float(t_r3d *r3d, int i)
{
	float	f;

	// ov.x = (1 + v.x) * 0.5 * r3d->width;
	// ov.y = (1 + v.y) * 0.5 * r3d->height;
	f = ((float)i / r3d->width / 0.5) - 1;
	return (f);
}

static t_color    blend_colors(t_color a, t_color b, float ratio)
{
	t_color	c;

	c.r = a.r * (1.0 - ratio) + b.r * ratio;
	c.g = a.g * (1.0 - ratio) + b.g * ratio;
	c.b = a.b * (1.0 - ratio) + b.b * ratio;
	return (c);
}

static void	draw_glyph(t_r3d *r3d, t_font *font, t_bakedchar ch, t_v2i pos)
{
	int			x;
	int			y;
	t_color		col;
	t_color		col2;
	int			index;

	x = 0;
	while (x < ch.width)
	{
		y = 0;
		while (y < ch.height)
		{
			col = ((t_color *) font->img->data)[(x + ch.x) + (y + ch.y) * font->img->width];
			index = (x + ch.xoffset + pos.x) + (y + ch.yoffset + pos.y) * r3d->width;
			col2 = r3d->color_buffer[index];
			if (col.t > 0)
			{
				col = blend_colors(col2, col, col.t / 255.0);
				r3d->color_buffer[index] = col;
			}
			y++;
		}
		x++;
	}
}

void	r3d_draw_text(t_r3d *r3d, t_font *font, char *text, t_v2 pos)
{
	const size_t	size = ft_strlen(text);
	t_v2i			spos;
	size_t			i;
	t_bakedchar		ch;

	spos = screen_coords(r3d, pos);
	i = 0;
	while (i < size)
	{
		if (text[i] < 0 || text[i] > 126)
		{
			i++;
			continue ;
		}
		ch = font->chars[(int) text[i]];
		draw_glyph(r3d, font, ch, spos);
		spos.x += ch.xadvance;
		i++;
	}
}

float	r3d_get_text_size(t_r3d *r3d, t_font *font, char *text)
{
	const size_t	size = ft_strlen(text);
	int				x;
	size_t			i;
	t_bakedchar		ch;

	x = 0;
	i = 0;
	while (i < size)
	{
		if (text[i] < 0 || text[i] > 126)
		{
			i++;
			continue ;
		}
		ch = font->chars[(int) text[i]];
		x += ch.xadvance;
		i++;
	}
	return (to_ndc_float(r3d, x));
}
