/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:20:07 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/16 21:21:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_H
# define V3_H

# include "v2.h"

typedef union s_v3
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	t_v2		xy;
} __attribute__((aligned(16)))	t_v3;

#endif
