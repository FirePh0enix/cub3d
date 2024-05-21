/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:30 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/21 17:05:22 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#define YELLOW	 "\033[0;33m"
#define GREEN	 "\033[0;32m"
#define BLUE	 "\033[0;34m"
#define RED		 "\033[0;31m"
#define PURPLE	 "\033[0;35m"
#define CYAN	 "\033[0;36m"
#define BLACK	 "\033[0;30"
#define WHITE	 "\033[0;37m"

static char	*gnl(char **line, int fd)
{
	*line = get_next_line(fd);
	return (*line);
}

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
// }

int	calc_map_height(char *path)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	if (!path)
		return (height);
	fd = open(path, O_RDONLY);
	while(gnl(&line, fd))
	{
		height++;
		free(line);
	}
	close (fd);
	return (height);
}

int	calc_map_width(char *path)
{
	int		fd;
	int		width;
	char	*line;

	width = 0;
	if (!path)
		return (width);
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	width = ft_strlen(line);
	close (fd);
	free(line);
	return (width);
}

void	map_to_tiles(char *path, t_map *map)
{
	char *maps;
	int	i;

	map->width = calc_map_width(path);
	map->height = calc_map_height(path);
	if (map->width == 0 || map->height == 0)
		return ;
	maps = NULL;
	maps = read_to_string(path);
	i = 0;
	map->tiles = ft_calloc(map->width * map->height, sizeof(int));
	while (i < map->height * map->width)
	{
		if ((maps[i] == '0' || maps[i] == ' '))
			map->tiles[i] = TILE_EMPTY;
		else
			map->tiles[i] = TILE_FULL;
		++i;
	}
}
