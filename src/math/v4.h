/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v4.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:09:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 18:10:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V4_H
# define V4_H

typedef struct s_v4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_v4;

inline t_v4	v4(float x, float y, float z, float w)
{
	return ((t_v4){x, y, z, w});
}

#endif
