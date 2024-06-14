/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 19:18:29 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static	bool	err_material(char *identifier)
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

static	bool	is_valid_number_ident(char **textures, int no, int so, int we)
{
	int		i;
	int		ea;
	char	*identifier;

	i = -1;
	ea = 0;
	while (textures[++i])
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
		return (false);
	return (true);
}

bool	fill_texture(t_map *map, char **maps)
{
	int		i;
	char	*identifier;
	char	**textures;
	t_image	*image;

	i = -1;
	textures = create_textures(maps);
	if (!is_valid_number_ident(textures, 0, 0, 0))
		return (false);
	while (textures[++i])
	{
		identifier = detect_identifier(textures[i]);
		if (is_valid_identifier_text(identifier))
		{
			image = load_texture(textures[i], identifier);
			if (!image)
				return (false);
			if (!create_material(identifier, map, image))
				return (err_material(identifier));
		}
		else
			return (err_identifier(identifier));
		free(identifier);
	}
	i = 0;
	while (i < 5)
	{
		if (textures[i])
		{
			textures[i] = NULL;
			free (textures[i]);
		}
		++i;
	}
	free(textures);
	return (true);
}
