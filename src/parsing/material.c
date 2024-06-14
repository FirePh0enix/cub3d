/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:56:28 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 15:57:36 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"


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
		ft_putstr_fd(RED"ERROR\nNO MATERIAL HAS NOT BEEN CREATED\n"RESET, 2);
		return (false);
	}
	else if (!map->so)
	{
		ft_putstr_fd(RED"ERROR\nSO MATERIAL HAS NOT BEEN CREATED\n"RESET, 2);
		return (false);
	}
	else if (!map->we)
	{
		ft_putstr_fd(RED"ERROR\nWE MATERIAL HAS NOT BEEN CREATED\n"RESET, 2);
		return (false);
	}
	else if (!map->ea)
	{
		ft_putstr_fd(RED"ERROR\nEA MATERIAL HAS NOT BEEN CREATED\n"RESET, 2);
		return (false);
	}
	else
		return (true);
}
