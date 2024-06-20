/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:16 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 18:17:59 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"
#include "mem.h"
#include <stddef.h>

t_scene	*create_scene(t_alloc_table *at)
{
	t_scene	*scene;

	scene = scalloc(at, 1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->entities = ft_vector(sizeof(t_entity *), 0, at);
	if (!scene->entities)
		return (free(scene), NULL);
	return (scene);
}

void	destroy_scene(t_scene *scene)
{
	ft_vector_free(scene->entities);
	free(scene);
}

void	scene_add_entity(t_scene *scene, void *entity)
{
	ft_vector_add(&scene->entities, &entity);
}

void	scene_remove_entity(t_scene *scene, t_entity *entity)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(scene->entities))
	{
		if (scene->entities[i] == entity)
		{
			ft_vector_del(scene, i);
			break ;
		}
		i++;
	}
}

t_entity	*scene_get_entity_by_id(t_scene *scene, int id)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(scene->entities))
	{
		if (scene->entities[i]->id == id)
			return (scene->entities[i]);
		i++;
	}
	return (NULL);
}
