/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:50:43 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 18:05:31 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static bool	invalid_rgb_char(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',' && color[i] != ' ')
		{
			ft_putstr_fd(RED"Error\n", 2);
			ft_putstr_fd(RED"Character "BRED, 2);
			ft_putchar_fd(color[i], 2);
			ft_putstr_fd(RED" is not allowed\n"RESET, 2);
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
			ft_putstr_fd(RED"Error\n"BRED, 2);
			putstr_sep(color + i, ',');
			ft_putstr_fd(RED" is not in RGB range (0-255)\n"RESET, 2);
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
