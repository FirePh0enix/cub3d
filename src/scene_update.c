/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:23:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/16 01:24:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

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