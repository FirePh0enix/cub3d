/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:12:43 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 17:47:20 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render/font.h"
#include "render/render.h"
#include <stdarg.h>

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
		// while (++i < num)
		// 	va_arg(list, char *);
		va_end(list);
		return (NULL);
	}
	while (++i < num)
		images[i] = tga_load_from_file(va_arg(list, char *)); // TODO: Check at the end of null pointers
	va_end(list);
	return (images);
}
