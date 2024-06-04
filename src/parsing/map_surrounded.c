/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_surrounded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:23 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/04 14:32:58 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	bool	is_map_border(int x, int y, t_map *map, char **maps)
{
	if (maps[y][x] == ' ')
		return (false);
	if (x <= 0 || x >= (int)ft_strlen(maps[y]) || y <= 0 || y >= map->height)
		return (true);
	if (y - 1 >= 0)
	{
		if (maps[y - 1][x] == ' ')
			return (true);
	}
	if (y + 1 < map->height)
	{
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
				printf(RED"MAP IS NOT SURROUNDED AT [%d][%d]"RESET, y ,x);
				return (false);
			}
			++x;
		}
		++y;
	}
	return (true);
}
