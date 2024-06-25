/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2i.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:50:33 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 22:00:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V2I_H
# define V2I_H

typedef struct s_v2i
{
	int	x;
	int	y;
}	t_v2i;

static inline	t_v2i	v2i(int x, int y)
{
	return ((t_v2i){x, y});
}

#endif
