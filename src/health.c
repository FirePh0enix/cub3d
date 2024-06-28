/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:44:40 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 19:05:17 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_health(t_vars *vars)
{
	char		buf[32];
	const int	percent = ((float)vars->map.player->health
			/ (float)MAX_HEALTH) * 100.0;

	ft_sprintf(buf, "%d %%", percent);
	font_draw_str(&vars->r3d, &vars->bffont, buf, posnscale((t_v2i){
			.x = 0,
			.y = 500
		}, 3));
}
