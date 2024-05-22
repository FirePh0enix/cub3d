/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:30 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/22 18:05:10 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "render/render.h"

#define YELLOW	 "\033[0;33m"
#define GREEN	 "\033[0;32m"
#define BLUE	 "\033[0;34m"
#define RED		 "\033[0;31m"
#define PURPLE	 "\033[0;35m"
#define CYAN	 "\033[0;36m"
#define BLACK	 "\033[0;30"
#define WHITE	 "\033[0;37m"

// static bool is_valid_character(char c)
// {
// 	if (c == '0')
// 		return (true);
// 	else if (c == '1')
// 		return (true);
// 	else if (c == 'N')
// 		return (true);
// 	else if (c == 'S')
// 		return (true);
// 	else if (c == 'E')
// 		return (true);
// 	else if (c == 'W')
// 		return (true);
// 	else if (c == ' ')
// 		return (true);
// 	else
// 	 	return (false);
// 

char	**create_map(char *path)
{
	// TODO: ADD ADDITIONAL SPACE TO MAKE THE MAP RECTANGULAR
	char	**maps;
	char	*line;

	maps = NULL;
	line = NULL;
	line = read_to_string(path);
	maps = ft_split(line, '\n');
	return (maps);
}

static int	calc_map_height(char **maps)
{
	int	i;

	i = 0;
	while (maps[i])
		++i;
	return (i);
}

static int	calc_map_max_width(char **maps)
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

void	map_to_tiles(char *path, t_map *map, char **map_split)
{
	char *maps;
	int	i;

	map->width = calc_map_max_width(map_split);
	map->height = calc_map_height(map_split);
	if (map->width == 0 || map->height == 0)
		return ;
	maps = NULL;
	maps = read_to_string(path);
	i = 0;
	map->tiles = ft_calloc(map->width * map->height + 1000, sizeof(int));
	while (maps[i])
	{
		if ((maps[i] == '0' || maps[i] == ' '))
			map->tiles[i] = TILE_EMPTY;
		else
			map->tiles[i] = TILE_FULL;
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
