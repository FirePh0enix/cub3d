/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/26 13:50:35 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include <stdbool.h>

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

bool	check_nb_identifer(int no, int so, int we, int ea)
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

static	bool	is_valid_number_ident(char **textures, int no, int so, int we)
{
	int		i;
	int		ea;
	char	*identifier;

	i = -1;
	ea = 0;
	while (++i < 4)
	{
		identifier = detect_identifier(textures[i]);
		if (!identifier)
			return (false);
		if (is_valid_identifier_text(identifier))
		{
			if (!ft_strcmp("NO", identifier))
				no++;
			else if (!ft_strcmp("SO", identifier))
				so++;
			else if (!ft_strcmp("WE", identifier))
				we++;
			else if (!ft_strcmp("EA", identifier))
				ea++;
		}
		free(identifier);
	}
	return (check_nb_identifer(no, so, we, ea));
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

	i = -1;
	if (!is_valid_number_ident(maps, 0, 0, 0))
		return (false);
	while (++i < 4)
	{
		identifier = detect_identifier(maps[i]);
		if (!identifier)
			return (false);
		if (is_valid_identifier_text(identifier))
		{
			if (!load_if_valid(maps[i], identifier, at, map))
				return (false);
		}
		else
			return (err_identifier(identifier));
		free(identifier);
	}
	return (true);
}
