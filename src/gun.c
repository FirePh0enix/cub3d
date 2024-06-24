/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:40:13 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/24 13:47:17 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gun.h"
#include "cub3d.h"
#include "math/v2i_basic.h"
#include "render/render.h"

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

static void	draw_crosshair(t_r3d *r3d)
{
	const int	w = r3d->width;
	const int	h = r3d->height;
	int			x;
	int			y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			r3d->color_buffer[(x + w / 2 - 4 / 2)
				+ (y + h / 2 - 4 / 2) * w] = hex(0x00FFFFFF);
			y++;
		}
		x++;
	}
}

void	draw_gun(t_gun *gun, t_r3d *r3d)
{
	float	scale;
	t_image	*image;
	t_v2i	pos;

	scale = 4;
	image = sprite_get_image(&gun->main_anim);
	pos = (t_v2i){r3d->width / 2.0 - image->width * scale / 2,
		r3d->height - image->height * scale};
	sprite_draw(r3d, &gun->main_anim, v2i_add(pos, gun->main_offset), scale);
	if (!gun->reloading && gun->has_shoot)
	{
		scale = 4;
		image = sprite_get_image(&gun->shoot_anim);
		pos = (t_v2i){r3d->width / 2.0 - image->width * scale / 2,
			r3d->height - image->height * scale};
		sprite_draw(r3d, &gun->shoot_anim, v2i_sub(pos, gun->offset), scale);
	}
	draw_crosshair(r3d);
}
