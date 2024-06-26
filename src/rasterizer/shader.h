/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:29:27 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 23:09:26 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "../render/render.h"
# include "../math/utils.h"

inline t_color	sample(t_image *img, t_v2 uv)
{
	int	x;
	int	y;

	x = uv.x * (img->w - 1);
	y = img->h - 1 - uv.y * (img->h - 1);
	x = clampf(x, 0, img->w - 1);
	y = clampf(y, 0, img->h - 1);
	return (((t_color *) img->data)[x + y * img->w]);
}

inline t_color	shader(
		t_r3d *r3d,
		t_v2 uv,
		t_image	*image,
		t_color col)
{
	t_color	pixel;

	(void) r3d;
	if (!image)
		pixel = col;
	else
		pixel = sample(image, uv);
	return (pixel);
}

#endif
