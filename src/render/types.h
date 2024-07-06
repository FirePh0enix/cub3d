/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:19:15 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/06 18:49:04 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "../math/v3.h"

/*
 * Some various types for the render engine.
 */

typedef union s_color
{
	unsigned int		raw;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	t;
	};
}	t_color;

t_color	hex(unsigned int hex);
t_color	rgba(unsigned char r, unsigned char g,
			unsigned char b, unsigned char t);
t_color	rgbaf(float r, float g, float b, float t);
t_color	grayscalef(float f);
t_color	color_scale(t_color col, float f);

typedef struct s_transform
{
	t_v3	position;
	t_v3	rotation;
}	t_transform;

#endif
