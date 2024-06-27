/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:39:30 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/27 11:58:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>
#include <stdint.h>

void	map_free(t_map *map, t_vars *vars)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	if (map->map_config)
	{
		while (map->map_config[i])
		{
			free(map->map_config[i]);
			++i;
		}
		free(map->map_config);
	}
	while (j < ft_vector_size(map->entities))
	{
		if (map->entities[j]->free)
			map->entities[j]->free(vars, map->entities[j]);
		free(map->entities[j]);
		++j;
	}
	ft_vector_free(map->entities);
}

void	map_reset(t_map *map)
{
	size_t	i;

	while (ft_vector_size(map->entities) > 1)
	{
		i = 0;
		while (i < ft_vector_size(map->entities))
		{
			if (map->entities[i]->type != ENTITY_PLAYER)
			{
				map_remove_entity(map, map->entities[i]);
				break ;
			}
			i++;
		}
	}
}
