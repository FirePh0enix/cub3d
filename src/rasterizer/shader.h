/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:29:27 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 13:21:12 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "../render/render.h"

inline t_color	shader(
		t_r3d *r3d,
		t_v2 uv,
		t_color col)
{
	t_color	pixel;

	pixel = col;
	// pixel = sample(mtl, uv);
	// TODO: Restore lighting when it works.
	// pixel.r *= light.r;
	// pixel.g *= light.g;
	// pixel.b *= light.b;
	return (pixel);
}

#endif
