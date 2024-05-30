/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:50:43 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/29 18:18:46 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

bool    is_rgb_range(char *s)
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
	while (j < 2)
	{
		colors[j] = map[i];
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

bool	check_rgb(char *color, t_map *map, char *identifier)
{
	int	i;
	int	j;
	int	rgb;

	i = 0;
	j = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' && color[i] != ' ')
		{
			printf(RED"CHARACTER %c iS NOT ALLOWED\n"WHITE, color[i]);
			return (false);
		}
		++i;
	}
	i = 0;
	while (color[i])
	{
		if (!is_rgb_range(color + i))
		{
			write(2, RED"ERROR: ", 7);
			putstr_sep(color + i, ',');
			write(2, " IS NOT IN RGB RANGE (0-255)\n"RESET, 29);
			return (false);
		}
		rgb = ft_atoi(color + i);
		fill_color(identifier, map, rgb, j);
		++j;
		i += ft_nblen(rgb);
		if (color[i] && color[i] == ',')
			++i;
	}
	return (true);
}

bool	is_valid_rgb(char **colors, t_map *map)
{
	int		i;
	char	*identifier;
	char	*color_path;

	i = 0;
	while (colors[i])
	{
		identifier = detect_identifier(colors[i]);
		if (is_valid_identifier_color(identifier))
		{
			color_path = detect_texture_path(colors[i]);
			if (!check_rgb(color_path, map, identifier))
				return (false);
		}
		free(identifier);
		++i;
	}
	return (true);
}