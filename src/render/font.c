/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:54:11 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/23 00:57:17 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "libft.h"
#include <stdio.h>

t_font	*font_create(t_alloc_table *at)
{
	char	buf[64];
	int		i;
	t_font	*font;

	font = scalloc(at, 1, sizeof(t_font));
	if (!font)
		return (NULL);
	font->images = scalloc(at, 127, sizeof(void *));
	if (!font->images)
		return (free(font), NULL);
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
	return (font);
}

t_image	*font_get_image(t_font *font, char c)
{
	if (c >= 'a' && c <= 'z')
		return (font->images[(int)c - 32]);
	return (font->images[(int)c]);
}

void	font_draw_str(t_r3d *r3d, t_font *font, char *str, t_v2i pos, float scale)
{
	size_t			x_adv;
	size_t			i;
	t_image			*image;

	if (font->images[33] == NULL)
		x_adv = 0;
	else
		x_adv = font->images[33]->width * scale * 1.5;
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
