/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:00:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/28 11:26:49 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render/render.h"

static void	load_shoot_anim2(t_sprite *sh, t_alloc_table *at)
{
	sh[BACK] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/5.tga",
				"assets/player/F/5.tga",
				"assets/player/G/5.tga"
				), 3, false, 100);
	sh[BACK_R] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/6.tga",
				"assets/player/F/6.tga",
				"assets/player/G/6.tga"
				), 3, false, 100);
	sh[RIGHT] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/7.tga",
				"assets/player/F/7.tga",
				"assets/player/G/7.tga"
				), 3, false, 100);
	sh[FORW_R] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/8.tga",
				"assets/player/F/8.tga",
				"assets/player/G/8.tga"
				), 3, false, 100);
}

static void	load_shoot_anim(t_sprite *sh, t_alloc_table *at)
{
	sh[FORW] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/1.tga",
				"assets/player/F/1.tga",
				"assets/player/G/1.tga"
				), 3, false, 100);
	sh[FORW_L] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/2.tga",
				"assets/player/F/2.tga",
				"assets/player/G/2.tga"
				), 3, false, 100);
	sh[LEFT] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/3.tga",
				"assets/player/F/3.tga",
				"assets/player/G/3.tga"
				), 3, false, 100);
	sh[BACK_L] = sprite_create_anim(load_images(at, 3,
				"assets/player/E/4.tga",
				"assets/player/F/4.tga",
				"assets/player/G/4.tga"
				), 3, false, 100);
}

#define WALK_MS 100

static void	load_main_anim2(t_sprite *sp, t_alloc_table *at)
{
	sp[BACK] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/5.tga",
				"assets/player/B/5.tga",
				"assets/player/C/5.tga",
				"assets/player/D/5.tga"
				), 4, true, WALK_MS);
	sp[BACK_R] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/6.tga",
				"assets/player/B/6.tga",
				"assets/player/C/6.tga",
				"assets/player/D/6.tga"
				), 4, true, WALK_MS);
	sp[RIGHT] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/7.tga",
				"assets/player/B/7.tga",
				"assets/player/C/7.tga",
				"assets/player/D/7.tga"
				), 4, true, WALK_MS);
	sp[FORW_R] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/8.tga",
				"assets/player/B/8.tga",
				"assets/player/C/8.tga",
				"assets/player/D/8.tga"
				), 4, true, WALK_MS);
}

static void	load_main_anim(t_sprite *sp, t_alloc_table *at)
{
	sp[FORW] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/1.tga",
				"assets/player/B/1.tga",
				"assets/player/C/1.tga",
				"assets/player/D/1.tga"
				), 4, true, WALK_MS);
	sp[FORW_L] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/2.tga",
				"assets/player/B/2.tga",
				"assets/player/C/2.tga",
				"assets/player/D/2.tga"
				), 4, true, WALK_MS);
	sp[LEFT] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/3.tga",
				"assets/player/B/3.tga",
				"assets/player/C/3.tga",
				"assets/player/D/3.tga"
				), 4, true, WALK_MS);
	sp[BACK_L] = sprite_create_anim(load_images(at, 4,
				"assets/player/A/4.tga",
				"assets/player/B/4.tga",
				"assets/player/C/4.tga",
				"assets/player/D/4.tga"
				), 4, true, WALK_MS);
}

void	load_skin(t_sprite *sp, t_sprite *sh, char *name, t_alloc_table *at)
{
	(void) name;
	load_shoot_anim(sh, at);
	load_shoot_anim2(sh, at);
	load_main_anim(sp, at);
	load_main_anim2(sp, at);
}
