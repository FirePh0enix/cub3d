/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:30 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/23 14:27:11 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "render/render.h"
#include <stddef.h>

#define YELLOW	 "\033[0;33m"
#define GREEN	 "\033[0;32m"
#define BLUE	 "\033[0;34m"
#define RED		 "\033[0;31m"
#define PURPLE	 "\033[0;35m"
#define CYAN	 "\033[0;36m"
#define BLACK	 "\033[0;30"
#define WHITE	 "\033[0;37m"

int	calc_map_height(char **maps)
{
	int	i;

	i = 0;
	while (maps[i])
		++i;
	return (i);
}

int	calc_map_max_width(char **maps)
{
	int	i;
	int	final_len;
	int	len;

	i = 0;
	final_len = 0;
	len = 0;
	while (maps[i])
	{
		len = ft_strlen(maps[i]);
		if (final_len < len)
			final_len = len;
		++i;
	}
	return (final_len);
}
char	**create_map(char *path, t_map *map)
{
	char	**maps;
	char	*line;

	maps = NULL;
	line = NULL;
	line = read_to_string(path);
	maps = ft_split(line, '\n');
	map->width = calc_map_max_width(maps);
	map->height = calc_map_height(maps);
	return (maps);
}

char	**fill_map_with_space(char **map, size_t width, size_t height)
{
	char	**new_map;
	size_t	i;

	new_map = NULL;
	new_map = ft_calloc(height + 1, sizeof(char *));
	i = 0;
	while (i < height)
	{
		if (ft_strlen(map[i]) < width)
		{
			new_map[i] = ft_calloc(width + 1, sizeof(char));
			ft_memset(new_map[i], ' ', width);
			ft_memcpy(new_map[i], map[i], ft_strlen(map[i]));
		}
		else
			new_map[i] = ft_strdup(map[i]);
		++i;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	map_to_tiles(t_map *map, char **maps)
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
			if (maps[i][j] == ' ' || maps[i][j] == '0')
				map->tiles[tile_index] = TILE_EMPTY;
			else
				map->tiles[tile_index] = TILE_FULL;
			++tile_index;
			++j;
		}
		++i;
	}
}

static bool is_map_border(int x, int y, t_map *map, char **maps)
{
	if (maps[y][x] == ' ')
		return (false);
	if (x <= 0 || x >= (int)ft_strlen(maps[y]) || y <= 0 || y >= map->height)
		return (true);
	if (y - 1 > 0)
	{
		if (x < (int)ft_strlen(maps[y - 1]))
			if (maps[y - 1][x] == ' ')
				return (true);
	}
	if (y + 1 < map->height)
	{
		if (x < (int)ft_strlen(maps[y + 1]))
			if (maps[y + 1][x] == ' ')
				return (true);
	}
	if (x + 1 < (int)ft_strlen(maps[y]))
	{
		if (maps[y][x + 1] == ' ')
			return (true);
	}
	if (x - 1 >= 0)
	{
		if (maps[y][x - 1] == ' ')
			return (true);
	}
	return (false);
}

bool	is_map_surrounded(char **maps, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (maps[y])
	{
		x = 0;
		while (maps[y][x])
		{
			if (is_map_border(x, y, map, maps) && maps[y][x] != '1')
			{
				printf("%d %d -> %c\n", y ,x, maps[y][x]);
				return (false);
			}
			++x;
		}
		++y;
	}
	return (true);
}
