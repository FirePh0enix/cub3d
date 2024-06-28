/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:07:47 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 16:32:31 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	ft_free(t_vars *vars, t_alloc_table *at)
{
	map_free(&vars->map, vars);
	sfreeall(at);
	if (vars->r3d.canvas)
		mlx_destroy_image(vars->mlx, vars->r3d.canvas);
	free(vars->minimap.rast.depth_buffer);
	return (0);
}
