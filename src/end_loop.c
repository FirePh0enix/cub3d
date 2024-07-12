/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 11:52:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	close_hook(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
}

void	game_loop(t_vars *vars)
{
	mlx_do_key_autorepeatoff(vars->mlx);
	mlx_loop(vars->mlx);
	mlx_do_key_autorepeaton(vars->mlx);
	ft_free(vars, &vars->at);
}
