#include "../cub3d.h"
#include "../parsing/parsing.h"

static bool	is_map_config_valid(t_vars *vars, char **map_config, t_alloc_table *at)
{
	if (!is_valid_char_in_map(vars->map->maps, vars->map))
		return (false);
	if (!is_map_surrounded(vars->map->maps, vars->map))
		return (false);
	if (!find_player_pos(vars->map->maps, vars->map))
		return (false);
	if (!fill_texture(vars->map, map_config, at))
		return (false);
	if (!is_valid_rgb(vars->map, map_config, at))
		return (false);
	if (!map_to_tiles(vars->map, vars->map->maps, vars->scene, vars, at))
		return (false);
	return (true);
}

bool	parsing(t_vars *vars, char **argv, t_alloc_table *at)
{
	char	*line;
	char	**map;

	line = read_to_string(argv[1], NULL, at);
	if (!line)
		return (false);
	vars->map = scalloc(at, sizeof(t_map), 1);
	if (!vars->map)
		return (false);
	vars->map->map_config = ft_split(line, '\n');
	if (!vars->map->map_config)
		return (false);
	if (!check_enough_line(vars->map->map_config))
		return (false);
	map = create_map(vars->map->map_config, vars->map, at);
	if (!map)
		return (false);
	vars->map->maps = fill_map_with_space(map, vars->map->width, vars->map->height, at);
	if (!vars->map->maps)
		return (false);
	if (!is_map_config_valid(vars, vars->map->map_config, at))
		return (false);
	return (true);
}
