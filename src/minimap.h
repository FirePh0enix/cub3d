/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:22:45 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 14:38:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "rasterizer/rasterizer.h"
# include "render/render.h"

typedef struct s_minimap
{
	t_image			*background;

	t_rasterizer	rast;
	t_map			*map;
}	t_minimap;

void	minimap_create(t_minimap *minimap, t_r3d *r3d, t_map *map);
void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_v2i pos, t_v2i mappos);

#endif
