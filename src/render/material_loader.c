/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:48 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/21 17:01:44 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "render.h"
#include "../cub3d.h"
#include <stdlib.h>

/*
 * Convert a path like `/home/ledelbec/Downloads/some_image.png` to
 * `some_image.tga`.
 */
static void convert_path(char *in, char *out, char *filename)
{
	const size_t sz = ft_strlen(in);
	size_t		i;
	size_t		j;
	char		*s;

	i = 0;
	j = 0;
	s = ft_strrchr(filename, '/');
	if (s)
	{
		s++;
		ft_memcpy(out, filename, s - filename);
		j += s - filename;
	}
	s = ft_strrchr(in, '/');
	if (s)
		i += s - in;
	while (i < sz + 1)
		out[j++] = in[i++];
	// FIXME Can segfault is out size < 3
	out[j - 4] = 't';
	out[j - 3] = 'g';
	out[j - 2] = 'a';
}

t_mtl	*mtl_load_from_file(t_vars *vars, char *name)
{
	const char	*str = read_to_string(name);
	char		**lines;
	char		*part;
	t_mtl		*material;
	char		texture[32];

	(void) vars;
	if (!str)
		return (NULL);
	material = malloc(sizeof(t_mtl));
	lines = ft_split(str, '\n');
	while (*lines)
	{
    	part = strtok(*lines, " ");
    	if (part == NULL || part[0] == 0 || strcmp(part, "map_Kd"))
		{
			lines++;
			continue;
		}
		part = strtok(NULL, " ");
		ft_bzero(texture, sizeof(texture));
		convert_path(part, texture, name);
		break;
		lines++;
	}
	material->image = tga_load_from_file(texture);
	return (material);
}
