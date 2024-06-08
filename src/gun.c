/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:40:13 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 22:04:26 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gun.h"
#include "cub3d.h"
#include "math/v2i_basic.h"
#include "render/render.h"

void	tick_gun(t_gun *gun)
{
	if (!gun->automatic)
	{
		if (gun->reloading)
		{
			gun->shoot_anim.current_frame = 0;
			gun->shoot_anim.last_frame_tick = getms();
			sprite_tick(&gun->main_anim);
			if (sprite_is_end(&gun->main_anim))
				gun->reloading = false;
		}
		else
		{
			gun->main_anim.current_frame = 0;
			gun->main_anim.last_frame_tick = getms();
			sprite_tick(&gun->shoot_anim);
			if (sprite_is_end(&gun->shoot_anim))
				gun->reloading = true;
		}
	}
}

void	draw_gun(t_gun *gun, t_r3d *r3d)
{
	float	scale;
	t_image	*image;
	t_v2i	pos;

	scale = 4;
	image = sprite_get_image(&gun->main_anim);
	pos = (t_v2i){r3d->width / 2.0 - image->width * scale / 2, r3d->height - image->height * scale};
	sprite_draw(r3d, &gun->main_anim, pos, scale);

	if (!gun->reloading)
	{
		scale = 4;
		image = sprite_get_image(&gun->shoot_anim);
		pos = (t_v2i){r3d->width / 2.0 - image->width * scale / 2, r3d->height - image->height * scale};
		sprite_draw(r3d, &gun->shoot_anim, v2i_sub(pos, gun->offset), scale);
	}
}