#include "cub3d.h"
#include "render/render.h"
#include <stdio.h>

static void	bake_wall(t_vars *vars, int x, int y, t_wall2 *w, t_map *map)
{
	const float	x2 =  x * WALL_SIZE;
	const float	y2 = -y * WALL_SIZE;
	const float	half = WALL_SIZE / 2.0;

	(void) vars;
	// w->no = wall(v3(x2, 0.0, y2 - half), M_PI, map->so);
	w->so = wall(v3(x2, 0.0, y2 + half), 0, map->so);
	// w->ea = wall(v3(x2 + half, 0.0, y2), M_PI / 2, map->so);
	// w->we = wall(v3(x2 - half, 0.0, y2), 3 * M_PI / 2, map->so);
}

void	bake_map(t_map *map, t_vars *vars)
{
	int	x;
	int	y;

	map->walls = ft_calloc(map->width * map->height, sizeof(t_wall2));
	if (!map->walls)
		return;

	map->so = mtl_new("South", vars->south);
	map->no = map->so;
	map->we = map->so;
	map->ea = map->so;

	printf("%d x %d\n", map->width, map->height);

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->tiles[x + y * map->width] == TILE_FULL)
				bake_wall(vars, x, y, &map->walls[x + y * map->width], map);
			else
				map->walls[x + y * map->width].is_empty = true;
			y++;
		}
		x++;
	}
}
