/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:54:11 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/22 14:25:00 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"

t_font	*font_load_from_file(char *filename, int x_size)
{
	t_font	*font;

	font = malloc(sizeof(t_font));
	if (!font)
		return (NULL);
	font->ppm = ppm_load_from_file(filename);
	if (!font->ppm)
		return (free(font), NULL);
	font->x_size = x_size;
	font->y_size = font->ppm->height;
	font->bg = 0xFFFFFFFF;
	return (font);
}

void	font_destroy(t_font *font)
{
	free(font);
}

int	font_x_offset(t_font *font, char c)
{
	return ((font->x_size) * ('A' - 32));
}
