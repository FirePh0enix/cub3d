/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:37:10 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/14 16:07:05 by ledelbec         ###   ########.fr       */
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
	// FIXME Might not be good, see sample_texture @ draw_walls.c
	x = uv.x * (mtl->image->width - 1);
	y = mtl->image->height - 1 - uv.y * (mtl->image->height - 1);
	x = clampf(x, 0, mtl->image->width - 1);
	y = clampf(y, 0, mtl->image->height - 1);
	return (((t_color *) mtl->image->data)[x + y * mtl->image->width]);
}

inline t_color	shader(
		t_r3d *r3d,
		t_mtl *mtl,
		float z,
		t_v2 uv,
		t_v3 light)
{
	t_color	pixel;

	if (r3d->mode == MODE_DEPTH)
		return (grayscalef(z));
	pixel = sample(mtl, uv);
	pixel.r *= light.r;
	pixel.g *= light.g;
	pixel.b *= light.b;
	return (pixel);
}

static t_v3 v3_mul_worldmatrix(t_r3d *r3d, t_v3 pos)
{
	const t_mat4	translation = mat4_translation(pos);
	const t_mat4	camera_trans = mat4_translation(v3_scale(r3d->camera->position, -1));

	return mat4_multiply_v3(mat4_mul_mat4(translation, camera_trans), pos);
}

#endif
