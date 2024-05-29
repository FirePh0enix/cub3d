/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:54:07 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/29 15:33:14 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_textures(char **map)
{
	char	**textures;
	int		i;

	i = 0;
	textures = NULL;
	textures = ft_calloc(5, sizeof(char *));
	while (i < 4)
	{
		textures[i] = map[i];
		++i;
	}
	return (textures);
}

char	*detect_texture_path(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] != ' ')
			++i;
		else
			break ;
	}
	++i;
	return (path + i);
}

t_image	*load_texture(char *textures, char *identifier)
{
	char	*textures_path;
	t_image	*image;

	textures_path = detect_texture_path(textures);
	image = tga_load_from_file(textures_path);
	if (!image)
	{
		printf(RED"ERROR: TGA LOADING FAILED for: %s\n", identifier);
		printf("Please verify the path: %s\n"RESET, textures_path);
		return (false);
	}
	return (image);
}
