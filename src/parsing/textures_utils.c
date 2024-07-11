/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:55:55 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/06 19:03:11 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

char	*texture_path(char *path)
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

t_image	*load_texture(char *textures, char *identifier, t_alloc_table *at)
{
	char	*textures_path;
	t_image	*image;

	textures_path = texture_path(textures);
	image = tga_load_from_file(textures_path, at);
	if (!image)
	{
		ft_putstr_fd(RED"Error\n", 2);
		ft_putstr_fd("TGA loading failed for: "BRED, 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd(RED"\nPlease verify the path: "BRED, 2);
		ft_putstr_fd(textures_path, 2);
		ft_putstr_fd("\n"RESET, 2);
		return (NULL);
	}
	return (image);
}

void	assign_textures(char *identifier, t_map *map, t_image *image)
{
	if (!ft_strcmp(identifier, "NO"))
		map->no = image;
	else if (!ft_strcmp(identifier, "SO"))
		map->so = image;
	else if (!ft_strcmp(identifier, "WE"))
		map->we = image;
	else if (!ft_strcmp(identifier, "EA"))
		map->ea = image;
}

bool	check_all_textures(t_map *map)
{
	if (!map->no)
		return (err_textures("NO"));
	else if (!map->so)
		return (err_textures("SO"));
	else if (!map->we)
		return (err_textures("WE"));
	else if (!map->ea)
		return (err_textures("EA"));
	else
		return (true);
}
