/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:12:43 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 14:55:04 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
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
			i = 0;
			while (i < num)
			{
				if (images[i])
					image_destroy(images[i]);
				i++;
			}
			free(images);
			return (NULL);
		}
		i++;
	}
	return (images);
}

t_image	**load_images(t_alloc_table *at ,int num, ...)
{
	va_list	list;
	int		i;
	t_image	**images;

	va_start(list, num);
	i = -1;
	images = ft_calloc(num, sizeof(t_image *));
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

static char	*dupbin(char *origin, size_t size, t_alloc_table *at)
{
	char	*new;

	new = salloc(at, size);
	ft_memcpy(new, origin, size);
	return (new);
}

char	*read_file(char *filename, t_alloc_table *at)
{
	char	*data;

	data = _get_file_data(filename);
	if (data)
		return (dupbin(data, _get_file_size(filename), at));
	printf("info : '%s' not embeded, reading from disk.\n", filename);
	return (read_to_string(filename, NULL));
}
