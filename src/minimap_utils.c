/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:08:55 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/08 16:25:31 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cub3d.h"

void	minimap_create(t_minimap *minimap, t_r3d *r3d, t_map *map)
{
	rasterizer_init_overlay(&minimap->rast, r3d, (t_rect){{0, 0},
	{WIDTH, HEIGHT}}, 70.0);
	minimap->map = map;
	minimap->bg = calc_avg_color(map);
}

t_color	blend(t_color fg, t_color bg)
{
	t_color			result;
	const uint32_t	alpha = (255 - fg.t) + 1;
	const uint32_t	inv_alpha = 256 - (255 - fg.t);

	result.r = (uint8_t)((alpha * fg.r + inv_alpha * bg.r) >> 8);
	result.g = (uint8_t)((alpha * fg.g + inv_alpha * bg.g) >> 8);
	result.b = (uint8_t)((alpha * fg.b + inv_alpha * bg.b) >> 8);
	result.t = 0x00;
	return (result);
}

t_color	calc_avg_color(t_map *map)
{
	int				pixel_count;
	unsigned long	r;
	unsigned long	g;
	unsigned long	b;
	int				i;

	if (!map->floor_image)
		return (rgba(map->floor_color.r, map->floor_color.g,
				map->floor_color.b, 0x99));
	pixel_count = map->floor_image->w * map->floor_image->h;
	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < pixel_count)
	{
		r += ((t_color *)map->floor_image->data)[i].r;
		g += ((t_color *)map->floor_image->data)[i].g;
		b += ((t_color *)map->floor_image->data)[i].b;
		i++;
	}
	return (rgba(r / pixel_count, g / pixel_count, b / pixel_count, 0x99));
}

bool	is_full(int tile)
{
	return (tile >= TILE_FULL && tile <= TILE_9);
}

void	draw_character(t_minimap *minimap, t_v3 pos)
{
	const t_mat4	m = mat4_translation(pos);
	t_tri			tri1;

	tri1 = (t_tri){
		.v0 = v3(+0.0, -0.4, +0.4),
		.v1 = v3(+0.4, +0.4, +0.4),
		.v2 = v3(-0.4, +0.4, +0.4),
	};
	tri1.v0 = mat4_multiply_v3(m, tri1.v0);
	tri1.v1 = mat4_multiply_v3(m, tri1.v1);
	tri1.v2 = mat4_multiply_v3(m, tri1.v2);
	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00FFFFFF));
}
