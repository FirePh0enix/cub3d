/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:25:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/03 22:44:28 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math/mat4_init.h"

t_wall	wall(t_v3 position, float rotation_y, t_image *img)
{
	t_wall	wall;

	wall = (t_wall){
		.w = WALL_SIZE,
		.h = WALL_SIZE,
		.pos = position,
		.rot_y = rotation_y,
		.rotation = mat4_rotation(v3(0, rotation_y, 0)),
		.inverse_rotation = mat4_rotation(v3(0, -rotation_y, 0)),
		.img = img
	};
	return (wall);
}
