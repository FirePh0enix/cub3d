/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:46:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/04 01:07:29 by ledelbec         ###   ########.fr       */
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

t_color	combine_light(t_color col, t_light *lights, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		if (lights[i].type == LIGHT_DIRECTIONAL)
		{
		}
		else if (lights[i].type == LIGHT_POINT)
		{
		}
	}
	return (col);
}
