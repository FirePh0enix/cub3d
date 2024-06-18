/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:05:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/18 13:38:25 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

void	putstr_sep(char *str, char n)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == n)
			break ;
		++i;
	}
	write (2, str, i);
}

bool	is_rgb_range(char *s)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (s[i] && s[i] != ',')
	{
		while (s[i] == ' ')
			i++;
		nbr = (nbr * 10 + s[i++] - '0');
		if (nbr > 255)
			return (false);
	}
	return (true);
}

char	**create_colors(char **map)
{
	char	**colors;
	int		i;
	int		j;

	i = 4;
	j = 0;
	colors = NULL;
	colors = ft_calloc(3, sizeof(char *));
	if (!colors)
	{
		ft_putstr_fd(RED"Error\nFailed to malloc colors\n"RESET, 2);
		return (NULL);
	}
	while (j < 2)
	{
		colors[j] = map[i];
		++i;
		++j;
	}
	return (colors);
}

int	ft_nblen(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

void	fill_color(char *identifier, t_map *map, unsigned char color, int i)
{
	if (!ft_strcmp(identifier, "F"))
	{
		if (i == 0)
			map->floor_color.r = color;
		else if (i == 1)
			map->floor_color.g = color;
		else if (i == 2)
			map->floor_color.b = color;
	}
	else if (!ft_strcmp(identifier, "C"))
	{
		if (i == 0)
			map->ceiling_color.r = color;
		else if (i == 1)
			map->ceiling_color.g = color;
		else if (i == 2)
			map->ceiling_color.b = color;
	}
}
