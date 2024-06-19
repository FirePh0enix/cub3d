/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/19 15:35:37 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

bool	err_textures(char *identifier)
{
	ft_putstr_fd(RED"Error\n"BRED, 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(RED" has not been created\n"RESET, 2);
	free_identifier(identifier);
	return (false);
}

static	bool	err_identifier(char *identifier)
{
	ft_putstr_fd(RED"Error\n", 2);
	ft_putstr_fd("Wrong identifier: "BRED, 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(RED"\nIdentifier should be: "BRED, 2);
	ft_putstr_fd("NO | SO | WE | EA\n"RESET, 2);
	free_identifier(identifier);
	return (false);
}

static char *which_ident_miss(int no, int so, int we, int ea)
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

static	bool	is_valid_number_ident(char **textures, int no, int so, int we)
{
	int		i;
	int		ea;
	char	*identifier;
	char	*miss_ident;

	i = -1;
	ea = 0;
	while (++i < 4)
	{
		identifier = detect_identifier(textures[i]);
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

bool	fill_texture(t_map *map, char **maps)
{
	int		i;
	char	*identifier;
	char	*textures[4];
	t_image	*image;

	i = -1;
	ft_bzero(textures, 4);
	while (++i < 4)
	{
		textures[i] = maps[i];
	}
	if (!is_valid_number_ident(textures, 0, 0, 0))
		return (false);
	i = -1;
	while (++i < 4)
	{
		identifier = detect_identifier(textures[i]);
		if (is_valid_identifier_text(identifier))
		{
			image = load_texture(textures[i], identifier);
			if (!image)
			{
				free(identifier);
				return (false);
			}
			if (!assign_textures(identifier, map, image))
				return (err_textures(identifier));
		}
		else
			return (err_identifier(identifier));
		free(identifier);
	}
	return (true);
}
