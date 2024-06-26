/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:40:13 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/29 16:14:57 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tick_gun(t_gun *gun)
{
	if (!gun->has_shoot)
	{
		gun->main_anim.current_frame = 0;
		gun->reloading = false;
		return ;
	}
	if (gun->reloading)
	{
		gun->shoot_anim.current_frame = 0;
		gun->shoot_anim.last_frame_tick = getms();
		sprite_tick(&gun->main_anim);
		if (sprite_is_end(&gun->main_anim))
		{
			gun->reloading = false;
			gun->has_shoot = false;
		}
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

void	draw_crosshair(t_r3d *r3d, t_vars *vars)
{
	const int	w = r3d->w;
	const int	h = r3d->h;
	const int	scale = 2;
	t_v2i		pos;

	if (!vars->crosshair)
		return ;
	pos.x = w / 2 - vars->crosshair->h * scale / 2;
	pos.y = h / 2 - vars->crosshair->w * scale / 2;
	sprite_draw_single(r3d, vars->crosshair, pos, scale);
}

void	draw_gun(t_gun *gun, t_r3d *r3d)
{
	float	scale;
	t_image	*image;
	t_v2i	pos;

	scale = 4;
	image = sprite_get_image(&gun->main_anim);
	if (!image)
		return ;
	pos = (t_v2i){r3d->w / 2.0 - image->w * scale / 2,
		r3d->h - image->h * scale};
	sprite_draw(r3d, &gun->main_anim, v2i_add(pos, gun->main_offset), scale);
	if (!gun->reloading && gun->has_shoot)
	{
		scale = 4;
		image = sprite_get_image(&gun->shoot_anim);
		pos = (t_v2i){r3d->w / 2.0 - image->w * scale / 2,
			r3d->h - image->h * scale};
		sprite_draw(r3d, &gun->shoot_anim, v2i_sub(pos, gun->offset), scale);
	}
}
