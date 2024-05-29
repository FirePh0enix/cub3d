/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/29 16:54:55 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	fill_texture(t_map *map, char **maps)
{
	int		i;
	char	*identifier;
	char	**textures;
	t_image	*image;

	i = 0;
	textures = create_textures(maps);
	while (textures[i])
	{
		identifier = detect_identifier(textures[i]);
		if (is_valid_identifier_text(identifier))
		{
			image = load_texture(textures[i], identifier);
			if (!image)
				return (false);
			if (!create_material(identifier, map, image))
			{
				printf(RED"ERROR: A MATERIAL HAS NOT BEEN TO CREATED CORRECTLY\n"RESET);
				return (false);
			}
		}
		else
		{
			printf(RED"ERROR: WRONG IDENTIFIER: %s\n", identifier);
			printf("FORMAT SHOULD BE : NO | SO | WE | EA\n"RESET);
			return (false);
		}
		free(identifier);
		++i;
	}
	return (true);
}
