/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:25:51 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/07 16:23:08 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "libft.h"

static t_v3	fill_position(int x, int y)
{
	return (v3(x, 0, y));
}

static t_v3	fill_rotation(char c)
{
	if (c == 'N')
		return (v3(0, 0, 0));
	else if (c == 'S')
		return (v3(0, M_PI, 0));
	else if (c == 'W')
		return (v3(0, M_PI / 2, 0));
	else if (c == 'E')
		return (v3(0, 3 * M_PI, 0));
	else
		return (v3(0, 0, 0));
}

bool	find_player_pos(char **maps, t_map *map)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (maps[y][x] == 'N' || maps[y][x] == 'S' || maps[y][x] == 'W'
				|| maps[y][x] == 'E')
			{
				map->spawns[i].position = fill_position(x, y);
				map->spawns[i].rotation = fill_rotation(maps[y][x]);
				map->spawn_count++;
				++i;
			}
			++x;
		}
		++y;
	}
	if (map->spawn_count == 0)
	{
		ft_putstr_fd(RED"ERROR\nPLACE ATLEAST 1 SPAWN: N | S | W | E\n", 2);
		return (false);
	}
	else
		return (true);
}
