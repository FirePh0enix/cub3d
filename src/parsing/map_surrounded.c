/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_surrounded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:23 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/09 15:20:26 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static	bool	error_surr(int y, int x)
{
	ft_putstr_fd(RED"Error\n", 2);
	ft_putstr_fd("Map is not surrounded at "BRED, 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd("]\n"RESET, 2);
	return (false);
}

static bool	is_wall(int x, int y, t_map *map, char **maps)
{
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

static	bool	is_map_border(int x, int y, t_map *map, char **maps)
{
	if (maps[y][x] == ' ')
		return (false);
	if (x <= 0 || x >= (int)ft_strlen(maps[y]) - 1
		|| y <= 0 || y >= map->height - 1)
		return (true);
	return (is_wall(x, y, map, maps));
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
				return (error_surr(y, x));
			}
			++x;
		}
		++y;
	}
	return (true);
}
