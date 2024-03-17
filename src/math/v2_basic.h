/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_basic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:36:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/17 23:09:17 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V2_BASIC_H
# define V2_BASIC_H

# include "v2.h"

inline t_v2	v2_add(t_v2 a, t_v2 b)
{
	return ((t_v2){a.x + b.x, a.y + b.y});
}

inline t_v2	v2_sub(t_v2 a, t_v2 b)
{
	return ((t_v2){a.x - b.x, a.y - b.y});
}

inline t_v2	v2_scale(t_v2 v, float s)
{
	return ((t_v2){v.x * s, v.y * s});
}

inline t_v2	v2_div(t_v2 v, float f)
{
	return ((t_v2){v.x / f, v.y / f});
}

#endif
