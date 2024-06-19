/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:12:43 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/19 15:48:27 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render/font.h"
#include "render/render.h"
#include <stdarg.h>
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

t_image	**load_images(int num, ...)
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
		images[i] = tga_load_from_file(va_arg(list, char *));
	va_end(list);
	return (check_images(num, images));
}
