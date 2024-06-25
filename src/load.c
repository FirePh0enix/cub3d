/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:12:43 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 22:22:45 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mem.h"
#include "parsing/parsing.h"
#include "render/font.h"
#include "render/render.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

static t_image	**check_images(int num, t_image **images)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (!images[i])
		{
			free(images);
			return (NULL);
		}
		i++;
	}
	return (images);
}

t_image	**load_images(t_alloc_table *at, int num, ...)
{
	va_list	list;
	int		i;
	t_image	**images;

	va_start(list, num);
	i = -1;
	images = scalloc(at, num, sizeof(t_image *));
	if (!images)
	{
		va_end(list);
		return (NULL);
	}
	// FIXME: If one file does not exist it can `malloc(): corrupted top`
	while (++i < num)
		images[i] = tga_load_from_file(va_arg(list, char *), at);
	va_end(list);
	return (check_images(num, images));
}

char	*read_file(char *filename, t_alloc_table *at)
{
	return (read_to_string(filename, NULL, at));
}
