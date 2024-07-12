/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:05:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 16:12:35 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include "libft.h"
#include <stddef.h>

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
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (s[i] && s[i] != ',')
	{
		while (s[i] == ' ')
			i++;
		if (!s[i] || s[i] == ',')
			return (false);
		nbr = (nbr * 10 + s[i++] - '0');
		if (nbr > 255)
			return (false);
	}
	return (true);
}

int	ft_nblen(char *s)
{
	int	len;

	len = 0;
	while (ft_isdigit(*s))
	{
		len++;
		s++;
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
