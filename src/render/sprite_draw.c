/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:40:33 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/29 16:03:50 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_draw(t_r3d *r3d, t_sprite *sprite, t_v2i pos, float scale)
{
	const t_image	*image = sprite_get_image(sprite);
	int				x;
	int				y;
	t_color			col;

	x = -1;
	if (!image || !sprite)
		return ;
	while (++x < image->w * scale)
	{
		y = -1;
		while (++y < image->h * scale)
		{
			if (x + pos.x < 0 || x + pos.x >= r3d->w || y + pos.y < 0
				|| y + pos.y >= r3d->h)
				continue ;
			col = ((t_color *) image->data)[(int)(x / scale)
				+ (int)(y / scale) *image->w];
			if (col.t == 0)
				r3d->color[(int)(x + pos.x)
					+ (int)(y + pos.y) *r3d->w] = col;
		}
	}
}

void	sprite_draw_single(t_r3d *r3d, t_image *image, t_v2i pos, float scale)
{
	int				x;
	int				y;
	t_color			col;

	x = -1;
	if (!image)
		return ;
	while (++x < image->w * scale)
	{
		y = -1;
		while (++y < image->h * scale)
		{
			if (x + pos.x < 0 || x + pos.x >= r3d->w || y + pos.y < 0
				|| y + pos.y >= r3d->h)
				continue ;
			col = ((t_color *) image->data)[(int)(x / scale)
				+ (int)(y / scale) *image->w];
			if (col.t == 0)
				r3d->color[(int)(x + pos.x)
					+ (int)(y + pos.y) *r3d->w] = col;
		}
	}
}
