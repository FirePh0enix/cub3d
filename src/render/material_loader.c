/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:48 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/16 16:01:48 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "render.h"
#include "../cub3d.h"
#include <stdlib.h>

static char *read_to_string(const char *filename)
{
	int fd;
	char *str;
	char buffer[4096];
	int str_size;
	int n;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
    	return (NULL);
	str = NULL;
	str_size = 0;
	n = 4096;
	while (n == 4096) {
	n = read(fd, buffer, 4096);
		if (n == -1)
			return (NULL);
	str = realloc(str, /*str_size + 1,*/ str_size + n + 1);
	if (!str)
		return (close(fd), NULL);
	ft_memcpy(str + str_size, buffer, n);
	str[str_size + n] = '\0';
	str_size += n;
	}
	return (close(fd), str);
}

/*
 * Convert a path like `/home/ledelbec/Downloads/some_image.png` to
 * `some_image.xpm`.
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
	while (i < sz + 1)
		out[j++] = in[i++];
	// FIXME Can segfault is out size < 3
	out[j - 4] = 'x';
	out[j - 3] = 'p';
	out[j - 2] = 'm';
}

t_mtl	*mtl_load_from_file(t_vars *vars, char *name)
{
	const char	*str = read_to_string(name);
	char		**lines;
	char		*part;
	t_mtl		*material;
	char		texture[32];
	int			w;

	if (!str)
		return (NULL);
	material = malloc(sizeof(t_mtl));
	lines = ft_split(str, '\n');
	while (*lines)
	{
    	part = strtok(*lines, " ");
    	if (part == NULL || part[0] == 0 || ft_strcmp(part, "map_Kd"))
		{
			lines++;
			continue;
		}
		part = strtok(NULL, " ");
		convert_path(part, texture, name);
		lines++;
	}
	material->image = mlx_xpm_file_to_image(vars->mlx, texture, &w, &w);
	return (material);
}
