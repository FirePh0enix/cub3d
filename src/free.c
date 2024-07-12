/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:07:47 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 11:54:11 by ledelbec         ###   ########.fr       */
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
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	if (vars->is_server && !(vars->server.socket == 0
			|| vars->server.socket == -1))
		close(vars->server.socket);
	else if (!vars->is_server && !(vars->client.socket == 0
			|| vars->client.socket == -1))
		close(vars->client.socket);
	return (0);
}
