/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:12:43 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/12 11:46:12 by ledelbec         ###   ########.fr       */
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
	while (++i < num)
		images[i] = tga_load_from_file(va_arg(list, char *), at);
	va_end(list);
	return (images);
}
