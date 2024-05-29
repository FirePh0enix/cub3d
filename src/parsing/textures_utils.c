/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:54:07 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/28 18:54:57 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_textures(char *map)
{
	char 	**textures;
	int		fd;
	int		i;

	fd = open(map, O_RDONLY);
	i = 0;
	textures = NULL;
	textures = ft_calloc(5, sizeof(char *));
	while (i < 4)
	{
		textures[i] = get_next_line(fd);
		++i;
	}
	textures[i] = NULL;
	close (fd);
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
	path[ft_strlen(path) - 1] = '\0';
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
		printf("Please verify the path: %s\n"WHITE, textures_path);
		return (false);
	}
	return (image);
}
