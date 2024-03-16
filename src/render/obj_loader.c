/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:45:49 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/16 16:04:29 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"
#include "libft.h"

static char	*read_to_string(char *filename)
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

static void	read_mtl(t_vars *vars, t_mesh *mesh, char **lines, char *filename)
{
	size_t	i;
	char	*mtllib;
	char	buffer[32];
	char	*s;

	i = 0;
	mtllib = NULL;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 7 && !ft_strncmp(lines[i], "mtllib ", 7))
		{
			mtllib = lines[i] + 7;
			break ;
		}
		i++;
	}
	if (!mtllib)
		return ;
	s = ft_strrchr(filename, '/');
	if (s)
	{
		s++;
		ft_memcpy(buffer, filename, s - filename);
		ft_memcpy(buffer + (s - filename), mtllib, ft_strlen(mtllib) + 1);
	}
	else
		ft_memcpy(buffer, mtllib, ft_strlen(mtllib) + 1);
	mesh->material = mtl_load_from_file(vars, buffer);
}

static void alloc_arrays(t_mesh *mesh, char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "v ", 2))
			mesh->vertices_count++;
		else if (ft_strlen(lines[i]) > 3 && !ft_strncmp(lines[i], "vt ", 3))
			mesh->textures_count++;
		else if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "f ", 2))
			mesh->faces_count++;
		i++;
	}
	mesh->vertices = malloc(sizeof(t_v3) * mesh->vertices_count);
	mesh->textures = malloc(sizeof(t_v2) * mesh->textures_count);
	mesh->faces = malloc(sizeof(t_face) * mesh->faces_count);
}

static void	read_face_nums(char *line, int index, t_face *face)
{
	char	*sv;
	char	*svt;
	char	*svn;

	sv = strtok(line, "/");
	svt = strtok(NULL, "/");
	svn = strtok(NULL, "/");
	if (sv == NULL || sv[0] == '\0')
		face->v[index] = -1;
	else
		face->v[index] = ft_atoi(sv) - 1;
	if (svt == NULL || svt[0] == '\0')
		face->t[index] = -1;
	else
		face->t[index] = ft_atoi(svt) - 1;
	if (svn == NULL || svn[0] == '\0')
		face->n[index] = -1;
	else
		face->n[index] = ft_atoi(svn) - 1;
}

static t_face	read_face(char *line)
{
	t_face	face;
	char	*s0;
	char	*s1;
	char	*s2;

	s0 = strtok(line, " ");
	s1 = strtok(NULL, " ");
	s2 = strtok(NULL, " ");
	read_face_nums(s0, 0, &face);
	read_face_nums(s1, 1, &face);
	read_face_nums(s2, 2, &face);
	return (face);
}

static void	read_arrays(t_mesh *mesh, char **lines)
{
	size_t	i;

	mesh->vertices_count = 0;
	mesh->textures_count = 0;
	mesh->faces_count = 0;
	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "v ", 2))
		{
			mesh->vertices[mesh->vertices_count++] = (t_v3){
				atof(strtok(lines[i] + 2, " ")),
				atof(strtok(NULL, " ")),
				atof(strtok(NULL, " ")),
			};
		}
		else if (ft_strlen(lines[i]) > 3 && !ft_strncmp(lines[i], "vt ", 3))
		{
			mesh->textures[mesh->textures_count++] = (t_v2){
				atof(strtok(lines[i] + 3, " ")),
				atof(strtok(NULL, " ")),
			};
		}
		else if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "f ", 2))
		{
			mesh->faces[mesh->faces_count++] = read_face(lines[i] + 2);
		}
		i++;
	}
}

t_mesh	*mesh_load_from_obj(t_vars *vars, char *filename)
{
	t_mesh		*mesh;
	const char	*str = read_to_string(filename);
	char		**lines;

	mesh = ft_calloc(1, sizeof(t_mesh));
	lines = ft_split(str, '\n');
	alloc_arrays(mesh, lines);
	read_mtl(vars, mesh, lines, filename);
	read_arrays(mesh, lines);
	if (!mesh_validate(mesh))
		return (NULL);
	return (mesh);
}

bool	mesh_validate(t_mesh *mesh)
{
	(void) mesh;
	return (true);
}
