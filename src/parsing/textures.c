/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:56:59 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/28 16:52:44 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "libft.h"

static char	**create_textures(char *map)
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

static	char	*detect_identifier(char *texture)
{
	int		i;
	char	*identifier;

	i = 0;
	identifier = NULL;
	identifier = ft_calloc(ft_strlen(texture) + 1, 1);
	while (texture[i])
	{
		if (texture[i] != ' ')
		{
			identifier[i] = texture[i];
			++i;
		}
		else
			break ;
	}
	return (identifier);
}

static char	*detect_texture_path(char *path)
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

bool	fill_texture(t_map *map, char *maps)
{
	int		i;
	char	*identifiers;
	char	*textures_path;
	int		id_count;
	t_image	*image;
	char	**textures;

	i = 0;
	id_count = 0;
	textures = NULL;
	textures = create_textures(maps);
	while (textures[i])
	{
		identifiers = detect_identifier(textures[i]);
		if (ft_strlen(identifiers) == 2)
		{
			id_count++;
			if (!ft_strcmp(identifiers, "NO"))
			{
				textures_path = detect_texture_path(textures[i]);
				image = tga_load_from_file(textures_path);
				if (!image)
				{
					printf(RED"ERROR: TGA LOADING FAILED %s\n"WHITE, textures_path);
					return (false);
				}
				map->no = mtl_new("NORTH", image);
				if (!map->no)
				{
					printf(RED"ERROR: MTL NEW FAILED\n"WHITE);
					return (false);
				}
			}
		}
		else
		{
			printf(RED"ERROR IDENTIFIER %s\n"WHITE, textures[i]);
			return (false);
		}
		++i;
	}
	if (id_count != 4)
	{
		printf(CYAN"ERROR IDENTIFIER COUNT SHOULD BE EQUAL TO 0\n"WHITE);
		return (false);
	}
	return (true);
}
