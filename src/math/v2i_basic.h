/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2i_basic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:36:31 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 20:03:31 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V2I_BASIC_H
# define V2I_BASIC_H

# include "v2i.h"

inline t_v2i	v2i_add(t_v2i a, t_v2i b)
{
	return ((t_v2i){a.x + b.x, a.y + b.y});
}

inline t_v2i	v2i_sub(t_v2i a, t_v2i b)
{
	return ((t_v2i){a.x - b.x, a.y - b.y});
}

#endif
