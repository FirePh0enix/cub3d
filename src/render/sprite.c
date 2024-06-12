/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:00:36 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/12 12:10:57 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "../cub3d.h"
#include "types.h"
#include <stdio.h>
#include <sys/select.h>

t_sprite	sprite_create(t_image *image)
{
	t_sprite	sprite;

	sprite.current_frame = 0;
	sprite.num_frames = 1;
	sprite.images = ft_calloc(sizeof(t_image *), 1);
	sprite.images[0] = image;
	sprite.ms = 0;
	sprite.last_frame_tick = 0;
	sprite.loop = false;
	return (sprite);
}

t_sprite	sprite_create_anim(t_image **images, int num, bool loop, suseconds_t ms)
{
	t_sprite	sprite;

	sprite.current_frame = 0;
	sprite.num_frames = num;
	sprite.last_frame_tick = getms();
	sprite.images = images;
	sprite.loop = loop;
	sprite.ms = ms;
	return (sprite);
}

t_image		*sprite_get_image(t_sprite *sprite)
{
	return (sprite->images[sprite->current_frame]);
}

bool		sprite_is_end(t_sprite *sprite)
{
	return (sprite->current_frame == sprite->num_frames - 1 && getms() - sprite->last_frame_tick >= sprite->ms);
}

void		sprite_tick(t_sprite *sprite)
{
	suseconds_t	elapsed;

	if (!sprite->loop && sprite->current_frame == sprite->num_frames - 1)
		return ;
	elapsed = getms() - sprite->last_frame_tick;
	if (elapsed < sprite->ms)
		return ;
	sprite->last_frame_tick = getms();

	if (++sprite->current_frame == sprite->num_frames)
	{
		if (sprite->loop)
			sprite->current_frame = 0;
		else
			sprite->current_frame = sprite->num_frames - 1;
	}
}

void		sprite_draw(t_r3d *r3d, t_sprite *sprite, t_v2i pos, float scale)
{
	const t_image	*image = sprite_get_image(sprite);
	int				x;
	int				y;
	t_color			col;

	x = -1;
	while (++x < image->width * scale)
	{
		y = -1;
		while (++y < image->height * scale)
		{
			if (x + pos.x < 0 || x + pos.x >= r3d->width || y + pos.y < 0 || y + pos.y >= r3d->height)
				continue ;
			col = ((t_color *) image->data)[(int)(x / scale) + (int)(y / scale) * image->width];
			if (col.t == 0)
				r3d->color_buffer[(int)(x + pos.x) + (int)(y + pos.y) * r3d->width] = col;
		}
	}
}

void		sprite_draw_single(t_r3d *r3d, t_image *image, t_v2i pos, float scale)
{
	int				x;
	int				y;
	t_color			col;

	x = -1;
	while (++x < image->width * scale)
	{
		y = -1;
		while (++y < image->height * scale)
		{
			if (x + pos.x < 0 || x + pos.x >= r3d->width || y + pos.y < 0 || y + pos.y >= r3d->height)
				continue ;
			col = ((t_color *) image->data)[(int)(x / scale) + (int)(y / scale) * image->width];
			if (col.t == 0)
				r3d->color_buffer[(int)(x + pos.x) + (int)(y + pos.y) * r3d->width] = col;
		}
	}
}
