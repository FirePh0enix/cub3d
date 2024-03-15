/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:19:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/15 16:01:38 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

static char	*read_to_string(const char *filename)
{
	int		fd;
	char	*str;
	char	buffer[4096];
	int		str_size;
	int		n;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = NULL;
	str_size = 0;
	n = 4096;
	while (n == 4096)
	{
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

static size_t	count_vertices(char **lines)
{
	size_t	n;

	n = 0;
	while (*lines)
	{
		if (ft_strncmp(*lines, "v ", 2) == 0)
			n++;
		lines++;
	}
	return (n);
}

static void	read_vertices(t_mesh *mesh, char **lines)
{
	int		i;
	char	*part;
	t_v3	v;

	i = 0;
	while (*lines)
	{
		if (ft_strncmp(*lines, "v ", 2) != 0)
		{
			lines++;
			continue ;
		}
		part = strtok(*lines, " ");
		part = strtok(NULL, " ");
		v.x = atof(part);
		part = strtok(NULL, " ");
		v.y = atof(part);
		part = strtok(NULL, " ");
		v.z = atof(part);
		mesh->vertices[i] = v;
		lines++;
		i++;
	}
}

static size_t	count_indices(char **lines)
{
	size_t	n;

	n = 0;
	while (*lines)
	{
		if (ft_strncmp(*lines, "f ", 2) == 0)
			n++;
		lines++;
	}
	return (n * 3);
}

static void	read_indices(t_mesh *mesh, char **lines)
{
	int		i;
	char	*part;

	i = 0;
	while (*lines)
	{
		if (ft_strncmp(*lines, "f ", 2) != 0)
		{
			lines++;
			continue ;
		}
		part = strtok(*lines, " ");
		// TODO Faces can be `<v>`, `<v>/<vn>` or `<v>/<vn>/<vt>`. For now this
		// will still works.
		part = strtok(NULL, " ");
		mesh->indices[i] = ft_atoi(part) - 1;
		part = strtok(NULL, " ");
		mesh->indices[i + 1] = ft_atoi(part) - 1;
		part = strtok(NULL, " ");
		mesh->indices[i + 2] = ft_atoi(part) - 1;
		lines++;
		i += 3;
	}
}

static void	convert_path(char *in, char *out)
{
	const size_t	sz = ft_strlen(in);

	ft_memcpy(out, in, sz + 1);
	out[sz - 3] = 'm';
	out[sz - 2] = 't';
	out[sz - 1] = 'l';
}

t_mesh	*mesh_load_from_file(const char *filename)
{
	const char	*str = read_to_string(filename);
	char		**lines;
	t_mesh		*mesh;
	char		mtl[32];

	convert_path((char *)filename, mtl);
	if (!str)
		return (NULL);
	lines = ft_split(str, '\n');
	if (!lines)
		return (NULL);
	mesh = malloc(sizeof(t_mesh));
	mesh->material = material_load(mtl);
	mesh->vertex_count = count_vertices(lines);
	mesh->vertices = malloc(sizeof(t_v3) * mesh->vertex_count);
	read_vertices(mesh, lines);
	mesh->index_count = count_indices(lines);
	mesh->indices = malloc(sizeof(int) * mesh->index_count);
	read_indices(mesh, lines);
	return (mesh);
}
