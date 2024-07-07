/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:27:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/07 17:01:06 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door(char **av, t_vars *v)
{
	if (!ft_strcmp(av[1], "maps/bonus/ac-origins.cub"))
		v->door = tga_load_from_file("assets/textures/egypt/DRFRONT.tga",
				&v->at);
	else if (!ft_strcmp(av[1], "maps/bonus/m4tr1x.cub"))
		v->door = tga_load_from_file("assets/textures/m4tr1x/COMP1B_4.tga",
				&v->at);
	else if (!ft_strcmp(av[1], "maps/bonus/volcano.cub"))
		v->door = tga_load_from_file("assets/textures/cave/CEIL1_2.tga",
				&v->at);
	else if (!ft_strcmp(av[1], "maps/bonus/star_wars.cub"))
		v->door = tga_load_from_file("assets/textures/star_wars/DOOR2_5.tga",
				&v->at);
	else
		v->door = tga_load_from_file("assets/textures/DOOR2_4.tga", &v->at);
}
