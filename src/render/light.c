/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:46:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/07 13:27:36 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <math.h>

inline float	clampf(float f, float min, float max)
{
	if (f > max)
		return (max);
	else if (f < min)
		return (min);
	return (f);
}

float	light_intensity(t_v3 light_dir, t_v3 n)
{
	return (clampf(v3_dot(light_dir, n), 0.1, 1.0));
}

t_v3	compute_lighting(t_light *lights, t_v3 pos, t_v3 n)
{
	const t_v3	ambient_light = v3(0.1, 0.1, 0.1);
	t_v3		col;
	size_t		i;
	t_light		*light;
	float		intensity;

	t_color		*color;
	t_v3		contrib;

	col = ambient_light;
	i = 0;
	while (i < ft_vector_size(lights))
	{
		light = &lights[i];
		if (light->type == LIGHT_DIRECTIONAL)
			intensity = light->intensity * clampf(v3_dot(light->direction, n), 0.0, 1.0);
		else if (light->type == LIGHT_POINT)
			intensity = light->intensity * clampf(v3_dot(v3_norm(v3_sub(pos, light->position)), n), 0.0, 1.0);

		color = &light->color;
		contrib = v3(color->r / 255.0, color->g / 255.0, color->b / 255.0);
		contrib.x *= intensity;
		contrib.y *= intensity;
		contrib.z *= intensity;

		col.x += contrib.x;
		col.y += contrib.y;
		col.z += contrib.z;
		i++;
	}
	col.r = clampf(col.r, 0.0, 1.0);
	col.g = clampf(col.g, 0.0, 1.0);
	col.b = clampf(col.b, 0.0, 1.0);
	return (col);
}
