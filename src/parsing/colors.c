/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:50:43 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/07 16:16:01 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	invalid_rgb_char(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' && color[i] != ' ')
		{
			printf(RED"CHARACTER %c iS NOT ALLOWED\n"WHITE, color[i]);
			return (false);
		}
		++i;
	}
	return (true);
}

bool	check_rgb(char *color, t_map *map, char *identifier)
{
	int	i;
	int	j;
	int	rgb;

	j = 0;
	i = 0;
	while (color[i])
	{
		if (!invalid_rgb_char(color))
			return (false);
		if (!is_rgb_range(color + i))
		{
			write(2, RED"ERROR\n", 6);
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
		if (!identifier)
			return (NULL);
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
