/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:27:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/01 18:29:11 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door(char **av, t_vars *v)
{
	if (!ft_strcmp(av[1], "maps/ac-origins.cub"))
		v->door = tga_load_from_file("assets/textures/egypt/DRFRONT.tga",
				&v->at);
	else
		v->door = tga_load_from_file("assets/textures/DOOR2_4.tga", &v->at);
}
