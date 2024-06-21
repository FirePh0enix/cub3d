#include "cub3d.h"
#include "parsing/parsing.h"

void	ft_free(t_vars *vars, t_alloc_table *at)
{
	for (int i = 0; vars->map->map_config[i]; i++) {
		free(vars->map->map_config[i]);
		vars->map->map_config[i] = NULL;
	}
	free(vars->map->map_config);

	sfreeall(at);

	free(at);
}
