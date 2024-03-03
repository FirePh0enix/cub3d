/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:10:07 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 16:13:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

t_mesh	*mesh_load_from_data(t_v3 *vertices, size_t vertex_count, int *indices, size_t index_count)
{
	t_mesh	*mesh;
	size_t	i;

	mesh = malloc(sizeof(t_mesh));
	mesh->vertex_count = vertex_count;
	mesh->vertices = malloc(sizeof(t_v3) * vertex_count);
	i = 0;
	while (i < vertex_count)
	{
		mesh->vertices[i] = vertices[i];
		i++;
	}
	mesh->index_count = index_count;
	mesh->indices = malloc(sizeof(int) * index_count);
	i = 0;
	while (i < index_count)
	{
		mesh->indices[i] = indices[i];
		i++;
	}
	return (mesh);
}

void	mesh_destroy(t_mesh *mesh)
{
	free(mesh->vertices);
	free(mesh);
}
