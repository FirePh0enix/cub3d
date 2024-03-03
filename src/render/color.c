/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:20:58 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 00:22:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	hex(unsigned int hex)
{
	return ((t_color){hex});
}

t_color	color_scale(t_color col, float f)
{
	col.r *= f;
	col.g *= f;
	col.b *= f;
	return (col);
}
