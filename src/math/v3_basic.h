/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_basic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:18:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/16 12:07:20 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_BASIC_H
# define V3_BASIC_H

# include "v3.h"
# include "v2.h"
# include "v2i.h"
# include <math.h>

inline t_v3	v3_add(t_v3 a, t_v3 b)
{
	return (v3(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline t_v3	v3_sub(t_v3 a, t_v3 b)
{
	return (v3(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline t_v3	v3_scale(t_v3 v, float scale)
{
	return (v3(v.x * scale, v.y * scale, v.z * scale));
}

inline t_v3	v3_div(t_v3 v, float scale)
{
	return (v3(v.x / scale, v.y / scale, v.z / scale));
}

#endif
