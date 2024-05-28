/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/28 19:13:58 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	fill_texture(t_map *map, char *maps)
{
	int		i;
	int		ident_count;
	char	*identifier;
	char	**textures;
	t_image	*image;

	i = 0;
	ident_count = 0;
	textures = create_textures(maps);
	while (textures[i])
	{
		identifier = detect_identifier(textures[i]);
		if (ft_strlen(identifier) == 2)
		{
			if (is_valid_identifier(identifier))
			{
				image = load_texture(textures[i], identifier);
				if (!image)
					return (false);
				if (!create_material(identifier, map, image))
					return (false);
				ident_count++;
			}
		}
		else
		{
			printf(RED"ERROR: IDENTIFIER LENGTH SHOULD BE EQUAL TO 2\n");
			printf("ACTUAL LENGTH IS (%d) for identifier: %s"WHITE, (int)ft_strlen(identifier) - 1, identifier);
			return (false);
		}
		++i;
	}
	if (ident_count != 4)
	{
		printf(RED"ERROR IDENTIFIER COUNT SHOULD BE EQUAL TO 4\n"WHITE);
		return (false);
	}
	return (true);
}
