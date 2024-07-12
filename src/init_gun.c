/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:44 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 11:31:52 by ledelbec         ###   ########.fr       */
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
	if (!vars->shotgun.main_anim.images)
		return (false);
	vars->shotgun.shoot_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/SHTFA0.tga",
				"assets/textures/SHTFB0.tga"
				), 2, false, 100);
	if (!vars->shotgun.shoot_anim.images)
		return (false);
	vars->shotgun.offset = (t_v2i){0, 96};
	vars->shotgun.main_offset = (t_v2i){-16, 0};
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
	if (!vars->pistol.main_anim.images)
		return (false);
	vars->pistol.shoot_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/PISFA0.tga", "assets/textures/PISFA0.tga"
				), 2, false, 100);
	if (!vars->pistol.shoot_anim.images)
		return (false);
	vars->pistol.main_offset = (t_v2i){24, 7};
	vars->pistol.offset = (t_v2i){0, 128 * 2 + 64};
	return (true);
}

static	bool	init_minigun(t_vars *vars)
{
	vars->minigun.main_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/CHGGA0.tga",
				"assets/textures/CHGGB0.tga"), 2, false, 30);
	if (!vars->minigun.main_anim.images)
		return (false);
	vars->minigun.shoot_anim = sprite_create_anim(load_images(&vars->at, 2,
				"assets/textures/CHGFA0.tga",
				"assets/textures/CHGFB0.tga"
				), 2, false, 30);
	if (!vars->shotgun.shoot_anim.images)
		return (false);
	vars->minigun.offset = (t_v2i){0, 132};
	return (true);
}

bool	init_weapons(t_vars *vars)
{
	if (!init_shotgun(vars))
		return (false);
	if (!init_pistol(vars))
		return (false);
	if (!init_minigun(vars))
		return (false);
	vars->crosshair = tga_load_from_file("assets/textures/PL_T.tga", &vars->at);
	return (true);
}
