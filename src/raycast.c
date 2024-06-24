#include "cub3d.h"
#include "libft.h"
#include "math/matrix.h"
#include "math/v3.h"
#include "scene.h"
#include <stdio.h>

static const char __test_tga[] = {};

static void *map[][2] = {
	{ "assets/texture/PLAYA1.tga", (void *)__test_tga }
};

char *get_file(char *name)
{
	for (size_t i = 0; i < sizeof(map) / sizeof(map[0]); i++)
	{
		if (!strcmp(name, map[i][0]))
			return (map[i][1]);
	}
	return (NULL);
}

static inline bool	is_full_tile(t_v3 v, t_map *map)
{
	return ((int)v.x >= 0 && (int)v.x <= map->width && (int)v.z >= 0
		&& (int)v.z <= map->height
		&& map->tiles[(int)v.x + (int)v.z * map->width] != TILE_EMPTY);
}

t_entity	*raycast_entity(t_map *map, t_transform ray, float size, uint32_t entity_type)
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
		v = v3_add(v3_add(ray.position, v3(0.5, 0.0, 0.5)), v3_scale(dir, precision * i));
		if (is_full_tile(v3_add(v, v3(0.5, 0.0, 0.5)), map))
			break ;
		j = 0;
		while (j < ft_vector_size(map->entities))
		{
			if (map->entities[j]->type == entity_type
				&& collide_point_vs_aabb(v,
					box_from_entity(map->entities[j])))
				return (map->entities[j]);
			j++;
		}
	}
	return (NULL);
}
