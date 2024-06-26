/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:22:45 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 14:31:48 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "mem.h"
# include "rasterizer/rasterizer.h"
# include "render/render.h"

typedef struct s_minimap
{
	t_rasterizer	rast;
	t_map			*map;

	t_color			bg;
}	t_minimap;

void	minimap_create(t_minimap *minimap, t_r3d *r3d, t_map *map);
void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_vars *vars);

#endif
