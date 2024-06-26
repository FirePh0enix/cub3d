/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:09:54 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 00:04:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS2_H
# define UTILS2_H

inline float	max2(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

inline float	min2(float x, float y)
{
	if (x < y)
		return (x);
	return (y);
}

inline float	abs2(float f)
{
	if (f < 0)
		return (-f);
	return (f);
}

inline int	mini2(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

inline int	maxi2(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

#endif
