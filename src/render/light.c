/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:46:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/05 16:16:20 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <math.h>

inline float	clampf(float f, float min, float max)
{
	return (fmaxf(min, fminf(f, max)));
}

float	light_intensity(t_v3 light_dir, t_v3 n)
{
	return (clampf(v3_dot(light_dir, n), 0.1, 1.0));
}

static t_color    blend_colors(t_color a, t_color b, float ratio)
{
	t_color	c;

	// c.r = a.r * (1.0 - ratio) + b.r * ratio;
	// c.g = a.g * (1.0 - ratio) + b.g * ratio;
	// c.b = a.b * (1.0 - ratio) + b.b * ratio;
	c.r = (int)((double)a.r) + ((double)b.r - (double)a.r * ratio);
	c.g = (int)((double)a.g) + ((double)b.g - (double)a.g * ratio);
	c.b = (int)((double)a.b) + ((double)b.b - (double)a.b * ratio);
	if (c.r > a.r)
		c.r = a.r;
	if (c.g > a.g)
		c.g = a.g;
	if (c.b > a.b)
		c.b = a.b;
	return (c);
}

t_color	combine_light(t_light *lights, t_v3 pos, t_v3 n)
{
	size_t	i;
	float	intensity;
	t_color	color;

	color = hex(0xFFFFFFFF);
	i = 0;
	while (i < ft_vector_size(lights))
	{
		if (lights[i].type == LIGHT_DIRECTIONAL)
			intensity = light_intensity(lights[i].direction, n)
				* lights[i].intensity;
		else if (lights[i].type == LIGHT_POINT)
			intensity = light_intensity(v3_sub(lights[i].position, pos), n)
				* lights[i].intensity;
		color = lights[i].color; // blend_colors(color, lights[i].color, intensity);
		// printf("%x\n", color.raw);
		i++;
	}
	return (color);
}

t_color	pixel_with_light(t_color pixel, t_color light)
{
	//pixel.r *= light.r / 0xFF;
	//pixel.g *= light.g / 0xFF;
	//pixel.b *= light.b / 0xFF;
	//return (pixel);
	return (light);
}
