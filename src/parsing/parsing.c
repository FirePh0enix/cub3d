#include "../cub3d.h"
#include "../parsing/parsing.h"

bool	parsing(t_vars *vars, char **argv)
{
	char	*line;
	char	**map_file;
	char	**map;

	vars->map = ft_calloc(sizeof(t_map), 1);
	line = read_to_string(argv[1], NULL);
	if (!line)
		return (false);
	map_file = ft_split(line, '\n');
	if (!check_enough_line(map_file))
		return (false);
	map = create_map(map_file, vars->map);
	if (!map)
		return (false);
	vars->map->maps = fill_map_with_space(map, vars->map->width, vars->map->height);
	if (!map_to_tiles(vars->map, vars->map->maps, vars->scene, vars))
		return (false);
	if (!is_valid_char_in_map(vars->map->maps, vars->map))
		return (false);
	if (!is_map_surrounded(vars->map->maps, vars->map))
		return (false);
	if (!find_player_pos(vars->map->maps, vars->map))
		return (false);
	if (!fill_texture(vars->map, map_file))
		return (false);
	if (!is_valid_rgb(vars->map, map_file))
		return (false);
	if (!is_valid_file_name(argv[1]))
		return (false);
	return (true);
}
