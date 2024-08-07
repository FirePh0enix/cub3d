/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:55:28 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 11:22:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

char	**create_map(char **cub_file, t_map *map, t_alloc_table *at)
{
	char	**maps;
	int		i;
	int		j;

	i = skip_until_map(cub_file);
	if (i == -1)
		return (NULL);
	j = 0;
	map->height = calc_map_height(cub_file);
	if (map->height == -1)
		return (NULL);
	maps = scalloc(at, map->height + 1, sizeof(char *));
	if (!maps)
	{
		ft_putstr_fd(RED"Error\nFailed to malloc maps (create_map)\n"RESET, 2);
		return (NULL);
	}
	while (cub_file[i])
		maps[j++] = cub_file[i++];
	map->width = calc_map_max_width(maps);
	return (maps);
}

static char	*create_longer_line(char *map, t_alloc_table *at, int wid)
{
	char	*new_map;

	new_map = scalloc(at, wid + 1, sizeof(char));
	if (!new_map)
	{
		ft_putstr_fd(RED"Error\nMalloc failed in (create_longer_line)", 2);
		return (NULL);
	}
	ft_memset(new_map, ' ', wid);
	ft_memcpy(new_map, map, ft_strlen(map));
	return (new_map);
}

char	**map_space(char **map, size_t wid, size_t hei, t_alloc_table *at)
{
	char	**new_map;
	size_t	i;

	new_map = scalloc(at, hei + 1, sizeof(char *));
	if (!new_map)
	{
		ft_putstr_fd(RED"Error\nMalloc failed for new map (map_space)\n"RESET,
			2);
		return (NULL);
	}
	i = -1;
	while (++i < hei)
	{
		if (ft_strlen(map[i]) < wid)
		{
			new_map[i] = create_longer_line(map[i], at, wid);
			if (!new_map[i])
				return (NULL);
		}
		else
			new_map[i] = map[i];
	}
	return (new_map);
}

static	bool	create_tile_array(t_map *map, t_alloc_table *at)
{
	map->tiles = scalloc(at, map->width * map->height, sizeof(int));
	if (!map->tiles)
	{
		ft_putstr_fd(RED"Error\nMalloc failed for map->tiles (map_to_tiles)\n"
			RESET,
			2);
		return (false);
	}
	return (true);
}

bool	map_to_tiles(t_map *map, char **maps, t_alloc_table *at)
{
	int		i;
	int		j;
	int		tile_index;

	i = 0;
	tile_index = 0;
	if (!create_tile_array(map, at))
		return (false);
	while (maps[i])
	{
		j = 0;
		while (maps[i][j])
		{
			if (maps[i][j] == 'D')
				map->tiles[tile_index] = TILE_DOOR;
			else if (maps[i][j] >= '1' && maps[i][j] <= '9')
				map->tiles[tile_index] = TILE_FULL + (maps[i][j] - '1');
			else
				map->tiles[tile_index] = TILE_EMPTY;
			++tile_index;
			++j;
		}
		++i;
	}
	return (true);
}
