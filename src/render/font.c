/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:54:11 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 22:46:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "libft.h"
#include <stdio.h>

bool	font_init(t_font *font, t_alloc_table *at)
{
	char	buf[64];
	int		i;

	i = 33;
	while (i < 126)
	{
		if (i < 100)
			ft_sprintf(buf, "assets/textures/STCFN0%d.tga", i);
		else
			ft_sprintf(buf, "assets/textures/STCFN%d.tga", i);
		font->images[i] = tga_load_from_file(buf, at);
		i++;
	}
	return (true);
}

bool	font_init_big(t_font *font, t_alloc_table *at)
{
	font->images['-'] = tga_load_from_file("assets/textures/STTMINUS.tga", at);
	font->images['%'] = tga_load_from_file("assets/textures/STTPRCNT.tga", at);
	font->images['0'] = tga_load_from_file("assets/textures/STTNUM0.tga", at);
	font->images['1'] = tga_load_from_file("assets/textures/STTNUM1.tga", at);
	font->images['2'] = tga_load_from_file("assets/textures/STTNUM2.tga", at);
	font->images['3'] = tga_load_from_file("assets/textures/STTNUM3.tga", at);
	font->images['4'] = tga_load_from_file("assets/textures/STTNUM4.tga", at);
	font->images['5'] = tga_load_from_file("assets/textures/STTNUM5.tga", at);
	font->images['6'] = tga_load_from_file("assets/textures/STTNUM6.tga", at);
	font->images['7'] = tga_load_from_file("assets/textures/STTNUM7.tga", at);
	font->images['8'] = tga_load_from_file("assets/textures/STTNUM8.tga", at);
	font->images['9'] = tga_load_from_file("assets/textures/STTNUM9.tga", at);
	return (true);
}

t_image	*font_get_image(t_font *font, char c)
{
	if (c >= 'a' && c <= 'z')
		return (font->images[(int)c - 32]);
	return (font->images[(int)c]);
}

static size_t	get_x_adv(t_font *font, float scale)
{
	t_image	*ref;
	size_t	x_adv;

	ref = font->images[33];
	if (!ref)
		ref = font->images[(int) '0'];
	if (!ref)
		x_adv = 0;
	else
		x_adv = ref->width * scale * 1.5;
	return (x_adv);
}

void	font_draw_str(t_r3d *r3d, t_font *font, char *str,
	t_v2i pos, float scale)
{
	size_t			x_adv;
	size_t			i;
	t_image			*image;

	x_adv = get_x_adv(font, scale);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == 32)
		{
			pos.x += x_adv;
			i++;
			return ;
		}
		image = font_get_image(font, str[i]);
		if (image)
			sprite_draw_single(r3d, image, pos, scale);
		pos.x += x_adv;
		i++;
	}
}
