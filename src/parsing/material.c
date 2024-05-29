/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:56:28 by vopekdas          #+#    #+#             */
/*   Updated: 2024/05/29 14:04:01 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	create_material(char *identifier, t_map *map, t_image	*image)
{
	if (!ft_strcmp(identifier, "NO"))
	{
		map->no = mtl_new("NORTH", image);
		if (!map->no)
			return (false);
	}
	else if (!ft_strcmp(identifier, "SO"))
	{
		map->so = mtl_new("SOUTH", image);
		if (!map->so)
			return (false);
	}
	else if (!ft_strcmp(identifier, "WE"))
	{
		map->we = mtl_new("WEST", image);
		if (!map->we)
			return (false);
	}
	else if (!ft_strcmp(identifier, "EA"))
	{
		map->ea = mtl_new("EAST", image);
		if (!map->ea)
			return (false);
	}
	return (true);
}

bool	check_all_materials(t_map *map)
{
	if (!map->no)
	{
		printf(RED"ERROR: NORTH MATERIAL HAS NOT BEEN CREATED\n"RESET);
		return (false);
	}
	else if (!map->so)
	{
		printf(RED"ERROR: SOUTH MATERIAL HAS NOT BEEN CREATED\n"RESET);
		return (false);
	}
	else if (!map->we)
	{
		printf(RED"ERROR: WEST MATERIAL HAS NOT BEEN CREATED\n"RESET);
		return (false);
	}
	else if (!map->ea)
	{
		printf(RED"ERROR: EAST MATERIAL HAS NOT BEEN CREATED\n"RESET);
		return (false);
	}
	else
		return (true);
}
