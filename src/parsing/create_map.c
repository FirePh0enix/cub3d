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
		ft_putstr_fd(RED"Error\nFailed to malloc maps (create_map)\n"RESET, 2);
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
		ft_putstr_fd(RED"Error\nMalloc failed for new map (fill_map_with_space)\n"RESET, 2);
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
				ft_putstr_fd(RED"Error\nMalloc failed for new_map[i] (fill_map_with_space)", 2);
				return (NULL);
			}
			ft_memset(new_map[i], ' ', width);
			ft_memcpy(new_map[i], map[i], ft_strlen(map[i]));
		}
		else
		{
			new_map[i] = ft_strdup(map[i]);
			if (!new_map[i])
			{
				ft_putstr_fd(RED"Error\nMalloc failed for new_map[i] (strdup)", 2);
				return (NULL);
			}
		}
		++i;
	}
	return (new_map);
}

bool	map_to_tiles(t_map *map, char **maps, t_scene *scene, t_vars *vars)
{
	int		i;
	int		j;
	int		tile_index;

	i = 0;
	tile_index = 0;
	map->tiles = ft_calloc(map->width * map->height, sizeof(int));
	if (!map->tiles)
	{
		ft_putstr_fd(RED"Error\nMalloc failed for map->tiles (map_to_tiles)", 2);
		return (false);
	}
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
				map->tiles[tile_index] = TILE_DOOR;
			}
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
