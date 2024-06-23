#include "cub3d.h"
#include "mlx.h"

void	ft_free(t_vars *vars, t_alloc_table *at)
{
	map_free(&vars->map, vars);
	sfreeall(at);
	if (vars->r3d.canvas)
		mlx_destroy_image(vars->mlx, vars->r3d.canvas);
}
