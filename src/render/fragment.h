/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:39:38 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/14 15:34:29 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGMENT_H
# define FRAGMENT_H

#include "render.h"

inline t_color	r3d_fragment(
		t_color in,
		t_opts *opts,
		float depth,
		t_v2i spos)
{
	// FIXME This costs us 0.03-0.04 ms for the teapot
	//if (opts->draw_depthbuffer)
	//	return (grayscalef(depth));
	
	return (grayscalef(depth));
}

#endif
