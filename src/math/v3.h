/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:20:07 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/30 13:38:20 by vopekdas         ###   ########.fr       */
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
	struct
	{
		float	r;
		float	g;
		float	b;
	};
	t_v2		xy;
} __attribute__((aligned(16)))	t_v3;

inline t_v3	v3(float x, float y, float z)
{
	return ((t_v3){{x, y, z}});
}

#endif
