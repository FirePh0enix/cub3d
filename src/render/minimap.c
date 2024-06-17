#include "font.h"
#include "render.h"
#include "../cub3d.h"
#include <stdio.h>

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
				put_tile(x, y, hex(0xFF000000), minimap->background);
			y++;
		}
		x++;
	}
}

#define WIDTH 300
#define HEIGHT 300
#define BORDER_WIDTH 6
#define CAM_WIDTH 10

static float	distance_circle(float x, float y, float center_x, float center_y)
{
	return (sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y)));
}

static void	print_camera(t_r3d *r3d, t_v2i pos, t_v2i mappos)
{
	const int	x = r3d->camera->position.x * RES + pos.x + RES / 2.0 - mappos.x;
	const int	y = r3d->camera->position.z * RES + pos.y + RES / 2.0 - mappos.y;

	int	i;
	int	j;

	i = -CAM_WIDTH / 2;
	while (i < CAM_WIDTH / 2)
	{
		j = -CAM_WIDTH / 2;
		while (j < CAM_WIDTH / 2)
		{
			r3d->color_buffer[(x + i) + (y + j) * r3d->width] = hex(0x00FFFFFF);
			j++;
		}
		i++;
	}
}

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
			int x2 = x + pos.x + RES / 2;
			int y2 = y + pos.y + RES / 2;

			if (x2 < 0 || x2 >= r3d->width || y2 < 0 || y2 >= r3d->height)
			{
				y++;
				continue ;
			}

			if (distance_circle(x, y, WIDTH / 2.0, HEIGHT / 2.0) > WIDTH / 2.0)
			{
				y++;
				continue ;
			}

			if (distance_circle(x, y, WIDTH / 2.0, HEIGHT / 2.0) > WIDTH / 2.0 - BORDER_WIDTH)
			{
				y++;
				r3d->color_buffer[x2 + y2 * r3d->width] = hex(0x00FFFFFF);
				continue ;
			}

			if (x + mappos.x < 0 || x + mappos.x >= minimap->background->width || y + mappos.y < 0 || y + mappos.y >= minimap->background->height)
				r3d->color_buffer[x2 + y2 * r3d->width] = hex(0xFF000000);
			else //if (((t_color *)minimap->background->data)[(x + mappos.x) + (y + mappos.y) * minimap->background->width].t == 0)
				r3d->color_buffer[x2 + y2 * r3d->width] = ((t_color *)minimap->background->data)[(x + mappos.x) + (y + mappos.y) * minimap->background->width];
			y++;
		}
		x++;
	}
	print_camera(r3d, pos, mappos);
}
