/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:37:10 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/19 21:41:30 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "render.h"

inline float	clampf(float f, float min, float max)
{
	return (fmaxf(min, fminf(f, max)));
}

inline t_color	sample(t_mtl *mtl, t_v2 uv)
{
	int	x;
	int	y;

	if (!mtl)
		return (hex(0xFFFFFFFF));
	x = uv.x * (mtl->image->width - 1);
	y = uv.y * (mtl->image->height - 1);
	x = (int) clampf(x, 0, mtl->image->width - 1);
	y = (int) clampf(y, 0, mtl->image->height - 1);
	// x = pos.x * mtl->image->width;
	// y = pos.y * mtl->image->height;
	return (((t_color *) mtl->image->data)[x + y * mtl->image->width]);
}

inline t_color	shader(t_r3d *r3d, t_mtl *mtl, float z, t_v2 uv)
{
	if (r3d->mode == MODE_DEPTH)
		return (grayscalef(z));
	return (sample(mtl, uv));
}

#endif
