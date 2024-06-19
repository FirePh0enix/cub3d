/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:54:07 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/19 15:33:59 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

char	**create_textures(char **map)
{
	char	**textures;
	int		i;

	i = 0;
	textures = NULL;
	textures = ft_calloc(5, sizeof(char *));
	if (!textures)
	{
		ft_putstr_fd(RED"Error\nMalloc failed for creating textures\n"RESET, 2);
		return (NULL);
	}
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
		ft_putstr_fd(RED"Error\n", 2);
		ft_putstr_fd("TGA loading failed for: "BRED, 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd(RED"\nPlease verify the path: "BRED, 2);
		ft_putstr_fd(textures_path, 2);
		ft_putstr_fd("\n"RESET, 2);
		return (false);
	}
	return (image);
}
bool	assign_textures(char *identifier, t_map *map, t_image *image)
{
	if (!ft_strcmp(identifier, "NO"))
	{
		map->no = image;
		if (!map->no)
			return (false);
	}
	else if (!ft_strcmp(identifier, "SO"))
	{
		map->so = image;
		if (!map->so)
			return (false);
	}
	else if (!ft_strcmp(identifier, "WE"))
	{
		map->we = image;
		if (!map->we)
			return (false);
	}
	else if (!ft_strcmp(identifier, "EA"))
	{
		map->ea = image;
		if (!map->ea)
			return (false);
	}
	return (true);
}

bool	check_all_textures(t_map *map)
{
	if (!map->no)
	{
		return (err_textures("NO"));
	}
	else if (!map->so)
	{
		return (err_textures("SO"));
	}
	else if (!map->we)
	{
		return (err_textures("WE"));
	}
	else if (!map->ea)
	{
		return (err_textures("EA"));
	}
	else
		return (true);
}
