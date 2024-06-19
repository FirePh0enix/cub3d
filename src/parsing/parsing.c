#include "../cub3d.h"
#include "../parsing/parsing.h"

static bool	is_map_config_valid(t_vars *vars, char **map_config)
{
	if (!is_valid_char_in_map(vars->map->maps, vars->map))
		return (false);
	if (!is_map_surrounded(vars->map->maps, vars->map))
		return (false);
	if (!find_player_pos(vars->map->maps, vars->map))
		return (false);
	if (!fill_texture(vars->map, map_config))
		return (false);
	if (!is_valid_rgb(vars->map, map_config))
		return (false);
	if (!map_to_tiles(vars->map, vars->map->maps, vars->scene, vars))
		return (false);
	return (true);
}

bool	parsing(t_vars *vars, char **argv)
{
	char	*line;
	char	**map_config;
	char	**map;

	if (!is_valid_file_name(argv[1]))
		return (false);
	line = read_to_string(argv[1], NULL);
	if (!line)
		return (false);
	vars->map = ft_calloc(sizeof(t_map), 1);
	if (!vars->map)
		return (false);
	map_config = ft_split(line, '\n');
	if (!check_enough_line(map_config))
		return (false);
	map = create_map(map_config, vars->map);
	if (!map)
		return (false);
	vars->map->maps = fill_map_with_space(map, vars->map->width, vars->map->height);
	if (!vars->map->maps)
		return (false);
	if (!is_map_config_valid(vars, map_config))
		return (false);
	return (true);
}
