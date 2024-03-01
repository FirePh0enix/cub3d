/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:21:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/01 22:50:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_v3	v3_add(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_v3	v3_sub(t_v3 a, t_v3 b)
{
	return ((t_v3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_v3	v3_scale(t_v3 v, float scale)
{
	return ((t_v3){v.x * scale, v.y * scale, v.z * scale});
}
