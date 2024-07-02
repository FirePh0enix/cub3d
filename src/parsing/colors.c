/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:50:43 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/02 12:50:54 by vopekdas         ###   ########.fr       */
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
	{
		map->floor_image = image;
	}
	else if (!ft_strcmp(identifier, "C"))
	{
		map->ceilling_image = image;
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
	return (ft_countchr(color, ',') == 2);
}

static bool	texture_fc(char *colors, char *iden, t_alloc_table *at, t_map *map)
{
	t_image	*image;

	image = load_texture(colors, iden, at);
	if (!image)
	{
		free(iden);
		return (false);
	}
	if (!create_image_fc(iden, map, image))
		return (false);
	return (true);
}

bool	is_valid_rgb(t_map *map, char **map_config, t_alloc_table *at)
{
	int		i;
	char	*identifier;

	i = -1;
	while (++i < 2)
	{
		if (!is_valid_number_fc(map_config))
			return (false);
		identifier = detect_identifier(map_config[i + 4]);
		if (!identifier)
			return (false);
		if (is_valid_identifier_color(identifier)
			&& !check_rgb(texture_path(map_config[i + 4]), map, identifier))
		{
			if ((_BONUS != 1)
				|| (!texture_fc(map_config[i + 4], identifier, at, map)))
			{
				free (identifier);
				return (false);
			}
		}
		free(identifier);
	}
	return (true);
}
