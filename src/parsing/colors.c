/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:50:43 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/09 12:33:55 by vopekdas         ###   ########.fr       */
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
		if (!ft_isdigit(color[i]) && color[i] != ',')
		{
			if (_BONUS == 1)
				return (false);
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

bool	create_image_fc(char *identifier, t_map *map, t_image *image)
{
	if (!ft_strcmp(identifier, "F"))
		map->floor_image = image;
	else if (!ft_strcmp(identifier, "C"))
		map->ceilling_image = image;
	return (true);
}

bool	check_rgb(char *color, t_map *map, char *identifier)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (color[i])
	{
		while (color[i] && color[i] == ' ')
			++i;
		if (!invalid_rgb_char(color) || !count_rgb(color))
			return (false);
		if (!is_rgb_range(color + i))
		{
			ft_putstr_fd(RED"Error\n"BRED, 2);
			putstr_sep(color + i, ',');
			ft_putstr_fd(RED" is not in RGB range (0-255)\n"RESET, 2);
			return (false);
		}
		fill_color(identifier, map, ft_atoi(color + i), j);
		++j;
		i += ft_nblen(ft_atoi(color + i));
		if (color[i] && color[i] == ',')
			++i;
	}
	return (ft_countchr(color, ',') == 2);
}

static bool	texture_fc(char *colors, char *iden, t_alloc_table *at, t_map *map)
{
	t_image	*image;

	image = load_texture(colors, iden, at);
	if (!image)
		return (false);
	if (!create_image_fc(iden, map, image))
		return (false);
	return (true);
}

bool	is_valid_rgb(t_map *map, char **map_config, t_alloc_table *at)
{
	int		i;
	char	*identifier;
	t_count	count;

	i = 0;
	count = (t_count){0};
	while (map_config[i])
	{
		identifier = detect_identifier(map_config[i]);
		if (!identifier)
			return (false);
		if (is_valid_identifier_color(identifier))
		{
			count_fc(identifier, &count.f, &count.c, &count.identifier_count);
			if (!check_rgb(texture_path(map_config[i]), map, identifier))
			{
				if ((_BONUS != 1)
					|| (!texture_fc(map_config[i], identifier, at, map)))
					return (free(identifier), (false));
			}
		}
		free(identifier);
		++i;
	}
	return (error_rgb(&count));
}
