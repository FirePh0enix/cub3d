#include "font.h"
#include "render.h"
#include "../cub3d.h"

#define RES 20

static void	put_tile(int x, int y, t_color col, t_image *image)
{
	int	i;
	int	j;

	i = 0;
	while (i < RES)
	{
		j = 0;
		while (j < RES)
		{
			((t_color *)image->data)[(x * RES + i) + (y * RES + j) * image->width] = col;
			j++;
		}
		i++;
	}
}

void	minimap_create(t_minimap *minimap, t_map *map)
{
	minimap->background = tga_create(map->width * RES, map->height * RES);
	if (!minimap->background)
		return ;
	minimap->final = tga_create(map->width * RES, map->height * RES);
	if (!minimap->final)
	{
		// TODO: Free background.
		return ;
	}

	int	x;
	int	y;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->tiles[x + y * map->width] == TILE_FULL)
				put_tile(x, y, hex(0x00FF0000), minimap->background);
			else
				put_tile(x, y, hex(0x00), minimap->background);
			y++;
		}
		x++;
	}
}

static void	print_camera(t_r3d *r3d, t_v2i pos, t_v2i mappos)
{
	const int	x = r3d->camera->position.x / WALL_SIZE * RES + pos.x + RES / 2.0 - mappos.x;
	const int	y = r3d->camera->position.z / WALL_SIZE * RES + pos.y + RES / 2.0 - mappos.y;

	int	i;
	int	j;

	i = -5;
	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{
			r3d->fb->color[(x + i) + (y + j) * r3d->fb->width] = hex(0x00FFFFFF);
			j++;
		}
		i++;
	}
}

#define WIDTH 300
#define HEIGHT 300

void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_v2i pos, t_v2i mappos)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x + pos.x < 0 || x + pos.x >= r3d->fb->width || y + pos.y < 0 || y + pos.y >= r3d->fb->height)
			{
				y++;
				continue ;
			}

			if (x + mappos.x < 0 || x + mappos.x >= minimap->background->width || y + mappos.y < 0 || y + mappos.y >= minimap->background->height)
				r3d->fb->color[(x + pos.x) + (y + pos.y) * r3d->fb->width] = hex(0);
			else
				r3d->fb->color[(x + pos.x) + (y + pos.y) * r3d->fb->width] = ((t_color *)minimap->background->data)[(x + mappos.x) + (y + mappos.y) * minimap->background->width];
			y++;
		}
		x++;
	}
	print_camera(r3d, pos, mappos);
}
