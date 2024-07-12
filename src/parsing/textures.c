/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 12:25:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include "libft.h"
#include <stdbool.h>

static bool	load_if_valid(char *maps, char *ide, t_alloc_table *at, t_map *map)
{
	t_image	*image;

	image = load_texture(maps, ide, at);
	if (!image)
	{
		free(ide);
		return (false);
	}
	assign_textures(ide, map, image);
	return (true);
}

static	bool	error_textures(char *identifier, int identifier_count)
{
	if (identifier_count > 4)
	{
		ft_fprintf(2,
			RED"Error\nOnly 4 textures are expected.\nFound: "
			BRED"%d"
			RED" instead.\n"RESET,
			identifier_count);
		free(identifier);
		return (false);
	}
	else if (ft_strcmp(identifier, "") && !is_valid_identifier_color(identifier)
		&& identifier_count < 4)
	{
		ft_fprintf(2,
			RED"Error\nFound an invalid identifier "
			BRED"%s\n"RESET,
			identifier);
		free(identifier);
		return (false);
	}
	return (true);
}

static	bool	error_count(int identifier_count)
{
	if (identifier_count != 4)
	{
		ft_fprintf(2,
			RED"Error\nFound "
			BRED"%d"RESET RED" identifier(s), but exactly 4 are required.\n"
			RESET, identifier_count);
		return (false);
	}
	return (true);
}

bool	fill_texture(t_map *map, char **maps, t_alloc_table *at)
{
	int		i;
	char	*identifier;
	int		identifier_count;

	i = 0;
	identifier_count = 0;
	while (maps[i])
	{
		identifier = detect_identifier(maps[i]);
		if (!identifier)
			return (false);
		if (is_valid_identifier_text(identifier))
		{
			if (!load_if_valid(maps[i], identifier, at, map))
				return (free(identifier), false);
			identifier_count++;
		}
		else if (!error_textures(identifier, identifier_count))
			return (false);
		free(identifier);
		++i;
	}
	return (error_count(identifier_count));
}
