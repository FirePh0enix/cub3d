/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:00:36 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 14:51:27 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

t_sprite	sprite_create(t_image *image, t_alloc_table *at)
{
	t_sprite	sprite;

	sprite.current_frame = 0;
	sprite.num_frames = 1;
	sprite.images = scalloc(at, sizeof(t_image *), 1);
	sprite.images[0] = image;
	sprite.ms = 0;
	sprite.last_frame_tick = 0;
	sprite.loop = false;
	return (sprite);
}

t_sprite	sprite_create_anim(t_image **images, int num, bool loop,
	suseconds_t ms)
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

t_image	*sprite_get_image(t_sprite *sprite)
{
	if (!sprite->images)
		return (NULL);
	return (sprite->images[sprite->current_frame]);
}

bool	sprite_is_end(t_sprite *sprite)
{
	return (sprite->current_frame == sprite->num_frames - 1
		&& getms() - sprite->last_frame_tick >= sprite->ms);
}

void	sprite_tick(t_sprite *sprite)
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
