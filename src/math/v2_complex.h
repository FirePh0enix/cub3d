/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_complex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:53:30 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/16 10:56:18 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V2_COMPLEX_H
# define V2_COMPLEX_H

# include "v2.h"
#include <math.h>

inline float	v2_length(t_v2 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

#endif
