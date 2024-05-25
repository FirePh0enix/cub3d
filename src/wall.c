/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:25:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/22 16:03:28 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math/mat4.h"
#include "math/mat4_init.h"
#include "math/v2.h"
#include "math/v3.h"

t_wall	wall(t_v3 position, float rotation_y, t_mtl *material)
{
	const float		half = WALL_SIZE / 2.0;
	const t_mat4	translation = mat4_translation(position);
	const t_mat4	rotation = mat4_rotation(v3(0, rotation_y, 0));
	t_wall			wall;

	t_v3 p0 = v3(-half,  half, 0);
	t_v3 p1 = v3( half,  half, 0);
	t_v3 p2 = v3(-half, -half, 0);

	wall = (t_wall){
		.w = WALL_SIZE,
		.h = WALL_SIZE,
		.pos = position,
		.rot_y = rotation_y,
		.n = mat4_multiply_v3(rotation, v3(0, 0, -1)),
		.material = material
	};

	// For raycasting
	wall.p0 = mat4_multiply_v3(rotation, p0);
	wall.p1 = mat4_multiply_v3(rotation, p1);
	wall.p2 = mat4_multiply_v3(rotation, p2);

	wall.p0 = mat4_multiply_v3(translation, wall.p0);
	wall.p1 = mat4_multiply_v3(translation, wall.p1);
	wall.p2 = mat4_multiply_v3(translation, wall.p2);

	t_v3	v0 = v3(-half,  half, 0);
	t_v3	v1 = v3( half,  half, 0);
	t_v3	v2 = v3( half, -half, 0);
	t_v3	_v3 = v3(-half, -half, 0);

	t_v2	t0 = {0.0, 0.0};
	t_v2	t1 = {1.0, 0.0};
	t_v2	t2 = {1.0, 1.0};
	t_v2	t3 = {0.0, 1.0};

	wall.t0.n0 = wall.n;
	wall.t0.n1 = wall.n;
	wall.t0.n2 = wall.n;
	wall.t0.v0 = v0;
	wall.t0.v1 = v1;
	wall.t0.v2 = _v3;
	wall.t0.t0 = t0;
	wall.t0.t1 = t1;
	wall.t0.t2 = t3;

	wall.t1.n0 = wall.n;
	wall.t1.n1 = wall.n;
	wall.t1.n2 = wall.n;
	wall.t1.v0 = v1;
	wall.t1.v1 = v2;
	wall.t1.v2 = _v3;
	wall.t1.t0 = t1;
	wall.t1.t1 = t2;
	wall.t1.t2 = t3;

	return (wall);
}
