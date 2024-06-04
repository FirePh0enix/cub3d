#include "cub3d.h"
#include "libft.h"
#include "math/mat4_init.h"
#include "math/v3.h"
#include "scene.h"
#include <stdio.h>

t_entity	*raycast_entity(t_scene *scene, t_transform ray, float size, uint32_t entity_type)
{
	const float precision = 0.1;
	const t_v3	dir = mat4_multiply_v3(mat4_rotation(ray.rotation), v3(0, 0, -1));

	// printf("%f %f %f\n", dir.x, dir.y, dir.z);

	int	len = size / precision;
	int	i = 0;
	size_t	j = 0;
	while (i < len)
	{
		t_v3	v = v3_add(ray.position, v3_scale(dir, precision * i));

		// printf("%f %f %f\n", v.x, v.y, v.z);

		j = 0;
		while (j < ft_vector_size(scene->entities))
		{
			t_entity *entity = scene->entities[j];
			if (entity->type == entity_type && collide_point_vs_aabb(v, box_from_entity(entity)))
				return (entity);
			j++;
		}
		i++;
	}

	return NULL;
}
