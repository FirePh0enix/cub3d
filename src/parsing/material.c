/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:56:28 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 18:35:52 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static	bool	err_material(char *identifier)
{
	ft_putstr_fd(RED"Error\n"BRED, 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(RED" has not been created\n"RESET, 2);
	return (false);
}

bool	create_material(char *identifier, t_map *map, t_image *image)
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

bool	check_all_materials(t_map *map)
{
	if (!map->no)
	{
		return (err_material("NO"));
	}
	else if (!map->so)
	{
		return (err_material("SO"));
	}
	else if (!map->we)
	{
		return (err_material("WE"));
	}
	else if (!map->ea)
	{
		return (err_material("EA"));
	}
	else
		return (true);
}
