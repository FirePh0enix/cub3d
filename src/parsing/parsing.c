/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:30 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 19:30:58 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include "libft.h"

char	**create_map(char **cub_file, t_map *map)
{
	char	**maps;
	int		i;
	int		j;

	i = 6;
	j = 0;
	map->height = calc_map_height(cub_file);
	maps = ft_calloc(map->height + 1, sizeof(char *));
	if (!maps)
	{
		ft_putstr_fd("Error\nFailed to malloc maps\n"RESET, 2);
		return (NULL);
	}
	while (cub_file[i])
		maps[j++] = cub_file[i++];
	map->width = calc_map_max_width(maps);
	return (maps);
}

char	**fill_map_with_space(char **map, size_t width, size_t height)
{
	char	**new_map;
	size_t	i;

	new_map = NULL;
	new_map = ft_calloc(height + 1, sizeof(char *));
	if (!new_map)
	{
		ft_putstr_fd(RED"Error\nMalloc failed for new map with space\n", 2);
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		if (ft_strlen(map[i]) < width)
		{
			new_map[i] = ft_calloc(width + 1, sizeof(char));
			if (!new_map[i])
			{
				ft_putstr_fd(RED"Error\nMAlloc failed for new_map[i]", 2);
				return (NULL);
			}
			ft_memset(new_map[i], ' ', width);
			ft_memcpy(new_map[i], map[i], ft_strlen(map[i]));
		}
		else
			new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			ft_putstr_fd(RED"Error\nMAlloc failed for new_map[i]", 2);
			return (NULL);
		}
		++i;
	}
	return (new_map);
}

void	map_to_tiles(t_map *map, char **maps, t_scene *scene, t_vars *vars)
{
	int		i;
	int		j;
	int		tile_index;

	i = 0;
	tile_index = 0;
	map->tiles = ft_calloc(map->width * map->height, sizeof(int));
	while (maps[i])
	{
		j = 0;
		while (maps[i][j])
		{
			if (maps[i][j] == 'D')
			{
				// t_door	*door = door_new(vars, scene, 0, next_entity_id(vars));
				// door->base.transform.position = v3(j * WALL_SIZE, 1.5, i * WALL_SIZE);
				// scene_add_entity(scene, door);
			}
			else if (maps[i][j] != '1')
				map->tiles[tile_index] = TILE_EMPTY;
			else
				map->tiles[tile_index] = TILE_FULL;
			++tile_index;
			++j;
		}
		++i;
	}
}
