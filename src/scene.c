/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:16 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 23:19:20 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	*create_scene()
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	scene->entities = ft_vector(sizeof(t_entity *), 0);
	scene->lights = ft_vector(sizeof(t_light), 9);
	return (scene);
}

void	scene_add_entity(t_scene *scene, void *entity)
{
	ft_vector_add(&scene->entities, &entity);
}

void	draw_scene(t_r3d *r3d, t_scene *scene, t_camera *camera)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(scene->entities))
	{
		if (scene->entities[i]->draw)
			scene->entities[i]->draw(r3d, scene->entities[i], camera);
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
