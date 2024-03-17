/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:39:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/17 23:30:00 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGMENT_H
# define FRAGMENT_H

#include "render.h"

inline float	clampf(float f, float min, float max)
{
	return (fmaxf(min, fminf(f, max)));
}

/*
 * Pos are in the [0.0; 1.0] range, so it needs to be converted to pixel
 * coordinates.
 */
inline t_color	sample(t_mtl *mtl, t_v2 pos)
{
	int	x;
	int	y;

	x = pos.x * (mtl->image->width - 1);
	y = pos.y * (mtl->image->height - 1);
	x = (int) clampf(x, 0, mtl->image->width - 1);
	y = (int) clampf(y, 0, mtl->image->height - 1);
	// x = pos.x * mtl->image->width;
	// y = pos.y * mtl->image->height;
	return (((t_color *) mtl->image->data)[x + y * mtl->image->width]);
}

inline t_color	r3d_fragment(
		t_r3d *r3d,
		t_mtl *mtl,
		float depth,
		t_v2 tpos)
{
	// FIXME This costs us 0.03-0.04 ms for the teapot
	if (r3d->mode == MODE_DEPTH)
		return (grayscalef(depth * 5.0));
	// return (rgbaf(tpos.x, 0.5, tpos.y, 1.0));
	return (sample(mtl, tpos));
	// return (hex(0xFF00FF00));
}

#endif
