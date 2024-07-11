/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rot.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:11:36 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/29 20:48:03 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_ROT_H
# define MAT4_ROT_H

# include "mat4.h"
# include "mat4_mul.h"
# include "v3.h"
# include "libft.h"
# include <math.h>

t_mat4	mat4_rotation(t_v3 angle);

#endif
