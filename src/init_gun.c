/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:44 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 16:55:02 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	bool	init_shotgun(t_vars *vars)
{
	vars->shotgun.main_anim = sprite_create_anim(load_images(&vars->at, 6,
				"assets/textures/SHTGA0.tga",
				"assets/textures/SHTGB0.tga",
				"assets/textures/SHTGC0.tga",
				"assets/textures/SHTGD0.tga",
				"assets/textures/SHTGC0.tga",
				"assets/textures/SHTGB0.tga"
				), 6, false, 100);
	vars->shotgun.shoot_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/SHTFA0.tga",
				"assets/textures/SHTFB0.tga"
				), 2, false, 100);
	vars->shotgun.offset = (t_v2i){-18, 96};
	return (true);
}

static	bool	init_pistol(t_vars *vars)
{
	vars->pistol.main_anim = sprite_create_anim(load_images(&vars->at, 8,
				"assets/textures/PISGA0.tga",
				"assets/textures/PISGB0.tga",
				"assets/textures/PISGC0.tga",
				"assets/textures/PISGD0.tga",
				"assets/textures/PISGE0.tga",
				"assets/textures/PISGD0.tga",
				"assets/textures/PISGC0.tga",
				"assets/textures/PISGB0.tga"
				), 8, false, 70);
	vars->pistol.shoot_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/PISFA0.tga", "assets/textures/PISFA0.tga"
				), 2, false, 100);
	vars->pistol.main_offset = (t_v2i){24, 7};
	vars->pistol.offset = (t_v2i){0, 128 * 2 + 64};
	return (true);
}

static	bool	init_minigun(t_vars *vars)
{
	vars->minigun.main_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/CHGGA0.tga",
				"assets/textures/CHGGB0.tga"), 2, false, 30);
	vars->minigun.shoot_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/CHGFA0.tga",
				"assets/textures/CHGFB0.tga"
				), 2, false, 30);
	vars->minigun.offset = (t_v2i){0, 132};
	return (true);
}

bool	init_weapons(t_vars *vars)
{
	init_shotgun(vars);
	init_pistol(vars);
	init_minigun(vars);
	vars->crosshair = tga_load_from_file("assets/textures/PL_T.tga", &vars->at);
	return (true);
}
