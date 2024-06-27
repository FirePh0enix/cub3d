/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:22:45 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:10:32 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "mem.h"
# include "rasterizer/rasterizer.h"
# include "render/render.h"

# define WIDTH 300
# define HEIGHT 300
# define BORDER_WIDTH 6
# define CAM_WIDTH 10

typedef struct s_minimap
{
	t_rasterizer	rast;
	t_map			*map;

	t_color			bg;
}	t_minimap;

void	minimap_create(t_minimap *minimap, t_r3d *r3d, t_map *map);
void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_vars *vars);

void	minimap_draw_cube(t_minimap *minimap, t_vars *vars, t_v3 pos);
void	minimap_draw_door(t_minimap *minimap, t_vars *vars, t_v3 pos);

void	mat4_mul_tri(t_mat4 m, t_tri *tri1, t_tri *tri2);

t_color	blend(t_color fg, t_color bg);
t_color	calc_avg_color(t_map *map);

#endif
