/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:16 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 13:27:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"
#include <stddef.h>

t_scene	*create_scene()
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	scene->entities = ft_vector(sizeof(t_entity *), 0);
	return (scene);
}

void	scene_add_entity(t_scene *scene, void *entity)
{
	ft_vector_add(&scene->entities, &entity);
}

void		scene_remove_entity(t_scene *scene, t_entity *entity)
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

void	draw_scene(t_r3d *r3d, t_scene *scene, t_camera *camera, t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(scene->entities))
	{
		if (scene->entities[i]->draw)
			scene->entities[i]->draw(r3d, scene->entities[i], camera, vars);
		i++;
	}
}

void	tick_scene(t_vars *vars, t_scene *scene)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(scene->entities))
	{
		if (scene->entities[i]->tick)
			scene->entities[i]->tick(vars, scene->entities[i]);
		i++;
	}
}
