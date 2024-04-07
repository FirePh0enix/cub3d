/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:27:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/07 17:57:17 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "render/render.h"
# include "scene.h"

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_r3d		*r3d;
	suseconds_t	last_update;

	t_scene		*scene;

	t_panel		*panel;
	t_font		*font;
}	t_vars;

#define WALL_SIZE 3.0

typedef struct s_wall
{
	t_v3	pos;
	float	w;
	float	h;
	float	rot_y;
	t_image	*img;
	t_v3	n;

	t_mat4	rotation;
	t_mat4	inverse_rotation;
}	t_wall;

t_wall	wall(t_v3 position, float rotation_y, t_image *img);

typedef struct s_map
{
	t_wall	*walls;
	int		width;
	int		height;
}	t_map;

#endif
