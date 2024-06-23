/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:19:59 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/23 18:24:38 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

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

void	map_free(t_map *map, t_vars *vars)
{
	for (int i = 0; map->map_config[i]; i++)
		free(map->map_config[i]);
	free(map->map_config);
	for (size_t i = 0; i < ft_vector_size(map->entities); i++)
	{
		if (map->entities[i]->free)
			map->entities[i]->free(vars, map->entities[i]);
		free(map->entities[i]);
	}
	ft_vector_free(map->entities);
}
