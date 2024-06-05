#include "cub3d.h"
#include "render/render.h"
#include <stdio.h>

static void	bake_wall(t_vars *vars, int x, int y, t_wall2 *w, t_map *map)
{
	const float	x2 = x * WALL_SIZE;
	const float	y2 = y * WALL_SIZE;
	const float	half = WALL_SIZE / 2.0;

	(void) vars;
	// w->no = wall(v3(x2, 0.0, y2 - half), M_PI, map->so);
	// w->ea = wall(v3(x2 + half, 0.0, y2), M_PI / 2, map->so);
	// w->we = wall(v3(x2 - half, 0.0, y2), 3 * M_PI / 2, map->so);

	// TODO:
	// If we switch to correct coordinates, everything below will probably need to be reversed.

	// if (y == 0 || map->tiles[x + (y - 1) * map->width] == TILE_EMPTY)
		w->so = wall(v3(x2, WALL_SIZE / 2, y2 + half), 0, map->so);
	// if (y == map->height - 1 || map->tiles[x + (y + 1) * map->width] == TILE_EMPTY)
		w->no = wall(v3(x2, WALL_SIZE / 2, y2 - half), M_PI, map->no);

	// if (x == 0 && map->tiles[(x - 1) + y * map->width] == TILE_EMPTY)
		w->ea = wall(v3(x2 - half, WALL_SIZE / 2, y2), 3 * M_PI / 2, map->ea);
	// if (x == map->width - 1 || map->tiles[(x + 1) + y * map->width] == TILE_EMPTY)
		w->we = wall(v3(x2 + half, WALL_SIZE / 2, y2), M_PI / 2, map->we);
}

void	bake_map(t_map *map, t_vars *vars)
{
	int	x;
	int	y;

	map->walls = ft_calloc(map->width * map->height, sizeof(t_wall2));
	if (!map->walls)
		return;

	// TODO: Check return values
	map->ceiling = mtl_color("ceiling", map->ceiling_color);
	map->floor = mtl_color("floor", map->floor_color);

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
