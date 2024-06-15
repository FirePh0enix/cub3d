#include "cub3d.h"
#include "libft.h"
#include "math/mat4_init.h"
#include "math/v3.h"
#include "scene.h"
#include <stdio.h>

static inline bool	is_full_tile(t_v3 v, t_map *map)
{
	return ((int)v.x >= 0 && (int)v.x <= map->width && (int)v.z >= 0
		&& (int)v.z <= map->height
		&& map->tiles[(int)v.x + (int)v.y * map->width] == TILE_FULL);
}

t_entity	*raycast_entity(t_map *map, t_scene *scene, t_transform ray,
	float size, uint32_t entity_type)
{
	const float	precision = 0.01;
	const t_v3	dir = mat4_multiply_v3(mat4_rotation(ray.rotation),
			v3(0, 0, -1));
	int			i;
	size_t		j;
	t_v3		v;

	i = -1;
	j = 0;
	while (++i < size / precision)
	{
		v = v3_add(ray.position, v3_scale(dir, precision * i));
		if (is_full_tile(v, map))
			break ;
		j = 0;
		while (j < ft_vector_size(scene->entities))
		{
			if (scene->entities[j]->type == entity_type
				&& collide_point_vs_aabb(v,
					box_from_entity(scene->entities[j])))
				return (scene->entities[j]);
			j++;
		}
	}
	return (NULL);
}
