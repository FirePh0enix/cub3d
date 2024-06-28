/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:55:44 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 18:41:36 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include "../hash.h"

static bool	is_map_config_valid(t_vars *vars, char **mp_conf, t_alloc_table *at)
{
	if (!is_valid_char_in_map(vars->map.maps, &vars->map))
		return (false);
	if (!is_map_surrounded(vars->map.maps, &vars->map))
		return (false);
	if (!find_player_pos(vars->map.maps, &vars->map))
		return (false);
	if (!fill_texture(&vars->map, mp_conf, at))
		return (false);
	if (!is_valid_rgb(&vars->map, mp_conf, at))
		return (false);
	if (!map_to_tiles(&vars->map, vars->map.maps, at))
		return (false);
	return (true);
}

static bool check_name_and_ac(int ac, char **av)
{
	if (ac != 2)
	{
		ft_fprintf(2, RED"Error: Incorrect number of arguments.\n");
		ft_fprintf(2, BRED"Usage: ./cub3d <map_file>\n"RESET);
		return (false);
	}
	if (!is_valid_file_name(av[1]))
		return (false);
	return (true);
}

static bool  check_map(t_vars *vars, t_alloc_table *at)
{
	char	**map;

	map = create_map(vars->map.map_config, &vars->map, at);
	if (!map)
		return (false);
	vars->map.maps = map_space(map, vars->map.width, vars->map.height, at);
	if (!vars->map.maps)
		return (false);
	if (!is_map_config_valid(vars, vars->map.map_config, at))
		return (false);
	return (true);
}

bool	parsing(t_vars *vars, char **argv, t_alloc_table *at, int ac)
{
	char	*line;

	vars->map.name = argv[1];
	if (!check_name_and_ac(ac, argv))
		return (false);
	line = read_to_string(argv[1], at);
	if (!line)
		return (false);
	vars->map.hash = fnv32_hash(line, ft_strlen(line));
	if (!map_init(&vars->map))
		return (false);
	vars->map.map_config = ft_split(line, '\n');
	if (!vars->map.map_config)
		return (false);
	if (!check_enough_line(vars->map.map_config))
		return (false);
	if (!check_map(vars, at))
		return (false);
	return (true);
}
