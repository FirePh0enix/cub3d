/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_convert.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:07:14 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/16 12:09:32 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_CONVERT_H
# define V3_CONVERT_H

# include "v3.h"
# include "v2.h"
# include "v2i.h"
# include <math.h>

inline t_v2i	v3_to_v2i(t_v3 v)
{
	return ((t_v2i){round(v.x), round(v.y)});
}

inline t_v2	v3_to_v2(t_v3 v)
{
	return ((t_v2){v.x, v.y});
}

#endif
