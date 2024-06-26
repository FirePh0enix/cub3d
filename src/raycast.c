/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:35:11 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 12:38:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "math/matrix.h"
#include "math/v2i.h"
#include "math/v3.h"
#include "scene.h"
#include <stdio.h>

static inline bool	is_full_tile(t_v3 v, t_map *map)
{
	int	tile;
	int	x;
	int	y;

	x = v.x;
	y = v.z;
	if (!(x >= 0 && x <= map->width && y >= 0 && y <= map->height))
		return (false);
	tile = map->tiles[x + y * map->width];
	return (tile >= TILE_FULL && tile <= TILE_9);
}

static t_entity	*collide_with_entity(t_map *map, t_v3 v, uint32_t entity_type)
{
	size_t	j;

	j = 0;
	while (j < ft_vector_size(map->entities))
	{
		if (map->entities[j]->type == entity_type
			&& collide_point_vs_aabb(v, box_from_entity(map->entities[j])))
			return (map->entities[j]);
		j++;
	}
	return (NULL);
}

t_entity	*raycast_entity(t_map *map, t_transform ray, float size,
	uint32_t entity_type)
{
	const float	precision = 0.01;
	const t_v3	dir = mat4_multiply_v3(mat4_rotation(ray.rotation),
			v3(0, 0, -1));
	int			i;
	t_v3		v;
	t_entity	*e;

	i = -1;
	while (++i < size / precision)
	{
		v = v3_add(v3_add(ray.position, v3(0, 0, 0)),
				v3_scale(dir, precision * i));
		if (is_full_tile(v3_add(v, v3(0.5, 0.0, 0.5)), map))
			break ;
		e = collide_with_entity(map, v, entity_type);
		if (e)
			return (e);
	}
	return (NULL);
}

t_v2i	raycast_door(t_map *map, t_transform ray, float size)
{
	const float	precision = 0.01;
	const t_v3	dir = mat4_multiply_v3(mat4_rotation(ray.rotation),
			v3(0, 0, -1));
	int			i;
	t_v3		v;
	t_v2i		p;

	i = -1;
	while (++i < size / precision)
	{
		v = v3_add(v3_add(ray.position, v3(0, 0, 0)),
				v3_scale(dir, precision * i));
		if (is_full_tile(v3_add(v, v3(0.5, 0.0, 0.5)), map))
			break ;
		p.x = v.x;
		p.y = v.z;
		if ((map->tiles[p.x + p.y * map->width] == TILE_DOOR
				|| map->tiles[p.x + p.y * map->width] == TILE_DOOR_OPEN)
			&& collide_point_vs_aabb(v, box_from_wall(p.x, p.y)))
			return (v2i(p.x, p.y));
	}
	return (v2i(-1, -1));
}
