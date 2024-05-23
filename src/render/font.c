/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:54:11 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/22 11:15:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "libft.h"
#include "../cub3d.h"

static void	read_char(t_font *font, char *line)
{
	char		**parts;
	int			id;
	t_bakedchar	ch;
	int			i;
	size_t		size;

	parts = ft_split(line, ' ');
	i = 0;
	while (parts[i])
	{
		size = ft_strlen(parts[i]);
		if (size > 3 && !ft_strncmp(parts[i], "id=", 3))
			id = ft_atoi(parts[i] + 3);
		else if (size > 2 && !ft_strncmp(parts[i], "x=", 2))
			ch.x = ft_atoi(parts[i] + 2);
		else if (size > 2 && !ft_strncmp(parts[i], "y=", 2))
			ch.y = ft_atoi(parts[i] + 2);
		else if (size > 6 && !ft_strncmp(parts[i], "width=", 6))
			ch.width = ft_atoi(parts[i] + 6);
		else if (size > 7 && !ft_strncmp(parts[i], "height=", 7))
			ch.height = ft_atoi(parts[i] + 7);
		else if (size > 8 && !ft_strncmp(parts[i], "xoffset=", 8))
			ch.xoffset = ft_atoi(parts[i] + 8);
		else if (size > 8 && !ft_strncmp(parts[i], "yoffset=", 8))
			ch.yoffset = ft_atoi(parts[i] + 8);
		else if (size > 9 && !ft_strncmp(parts[i], "xadvance=", 9))
			ch.xadvance = ft_atoi(parts[i] + 9);
		else if (size > 5 && !ft_strncmp(parts[i], "page=", 5))
			ch.page = ft_atoi(parts[i] + 5);
		else if (size > 5 && !ft_strncmp(parts[i], "chnl=", 5))
			ch.chnl = ft_atoi(parts[i] + 5);
		free(parts[i]);
		i++;
	}
	font->chars[id] = ch;
	free(parts);
}

static void	read_fnt(t_font *font, char *filename)
{
	const char	*s = read_to_string(filename);
	const char	**lines = (const char **) ft_split(s, '\n');
	int			i;

	i = 0;
	while (lines[i])
	{
		if (!ft_strncmp(lines[i], "char ", 5))
			read_char(font, (char *) lines[i]);
		free((void *) lines[i]);
		i++;
	}
	free(lines);
}

t_font	*font_load_from_file(char *filename)
{
	const size_t	size = ft_strlen(filename);
	t_font	*font;
	char	buf[256];

	font = ft_calloc(1, sizeof(t_font));
	if (!font)
		return (NULL);
	font->img = tga_load_from_file(filename);
	ft_memcpy(buf, filename, size + 1);
	buf[size - 3] = 'f';
	buf[size - 2] = 'n';
	buf[size - 1] = 't';
	read_fnt(font, buf);
	return (font);
}

void	font_destroy(t_font *font)
{
	free(font);
}
