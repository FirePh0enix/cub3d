/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:30:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 18:31:05 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERIZE_UTILS_H
# define RASTERIZE_UTILS_H

# include "rasterizer.h"

inline float	edge_fn(t_v3 a, t_v3 b, t_v3 c)
{
	return ((a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x));
}

/*
 * Two steps are necessary to correctly interpolate a value:
 * - Divide every values by their associated z vertex component.
 * - Compute the interpolate value.
 */

inline void	pint_v2(t_v2 *v0, t_v2 *v1, t_v2 *v2, t_tri *tri)
{
	v0->x /= tri->v0.z;
	v0->y /= tri->v0.z;
	v1->x /= tri->v1.z;
	v1->y /= tri->v1.z;
	v2->x /= tri->v2.z;
	v2->y /= tri->v2.z;
}

inline t_v2	int_v2(t_v2 v0, t_v2 v1, t_v2 v2, t_v4 w)
{
	return ((t_v2){
		(w.x * v0.x + w.y * v1.x + w.z * v2.x) * w.w,
		(w.x * v0.y + w.y * v1.y + w.z * v2.y) * w.w,
	});
}

inline	t_v4	make_w(t_tri tri, t_v3 p)
{
	return (v4(edge_fn(tri.v1, tri.v2, p), edge_fn(tri.v2, tri.v0, p),
			edge_fn(tri.v0, tri.v1, p), 0));
}

#endif