/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:46:04 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 12:44:12 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vec.h"

typedef struct t_mat4
{
	float	data[4][4];
}	t_mat4;

t_mat4	mat4_identity(void);
t_mat4	mat4_mul_v3(t_mat4 mat, t_v3 v);

#endif
