/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/06 19:29:07 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include "libft.h"

static char	*which_ident_miss(int no, int so, int we, int ea)
{
	if (no == 0)
		return ("NO");
	else if (so == 0)
		return ("SO");
	else if (we == 0)
		return ("WE");
	else if (ea == 0)
		return ("EA");
	else
		return (0);
}

bool	check_nb_identifier(int no, int so, int we, int ea)
{
	char	*miss_ident;

	if (no != 1 || so != 1 || we != 1 || ea != 1)
	{
		miss_ident = which_ident_miss(no, so, we, ea);
		ft_putstr_fd(RED"Error\n", 2);
		ft_putstr_fd("Identifier "BRED, 2);
		ft_putstr_fd(miss_ident, 2);
		ft_putstr_fd(RED" is missing\n"RESET, 2);
		return (false);
	}
	return (true);
}

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
				return (false);
			identifier_count++;
		}
		else if (ft_strcmp(identifier, "") && !is_valid_identifier_color(identifier))
		{
			ft_fprintf(2, RED"Error\nFound an invalid identifier "BRED"%s\n"RESET, identifier);
			free(identifier);
			return (false);
		}
		free(identifier);
		++i;
	}
	if (identifier_count != 4)
	{
		ft_fprintf(2, RED"Error\nFound "BRED"%d"RESET RED" identifier(s), but exactly 4 are required.\n"RESET, identifier_count);
		return (false);
	}
	return (true);
}
