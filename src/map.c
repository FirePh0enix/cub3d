/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:19:59 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 16:39:43 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_add_entity(t_map *map, void *entity)
{
	ft_vector_add(&map->entities, &entity);
}

void	map_remove_entity(t_map *map, void *entity)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(map->entities))
	{
		if (map->entities[i] == entity)
		{
			ft_vector_del(&map->entities, i);
			break ;
		}
		i++;
	}
}

void	*map_get_entity_by_id(t_map *map, int id)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(map->entities))
	{
		if (map->entities[i]->id == id)
			return (map->entities[i]);
		i++;
	}
	return (NULL);
}

void	map_tick(t_vars *vars, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_size(map->entities))
	{
		if (map->entities[i]->tick)
			map->entities[i]->tick(vars, map->entities[i]);
		i++;
	}
}

bool	map_init(t_map *map)
{
	map->entities = ft_vector(sizeof(t_entity *), 0);
	if (!map->entities)
		return (false);
	map->player = NULL;
	return (true);
}
