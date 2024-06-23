#include "minimap.h"
#include "cub3d.h"
#include "math/mat4.h"
#include "math/mat4_init.h"
#include "math/mat4_mul.h"
#include "mem.h"
#include "rasterizer/rasterizer.h"
#include "render/render.h"
#include "render/types.h"
#include <stdio.h>

#define WIDTH 300
#define HEIGHT 300
#define BORDER_WIDTH 6
#define CAM_WIDTH 10

static t_color calc_avg_color(t_map *map)
{
	int				pixel_count;
	unsigned long	r;
	unsigned long	g;
	unsigned long	b;
	t_color			col;
	int				i;

	if (!map->floor_image)
		return (rgba(map->floor_color.r, map->floor_color.g, map->floor_color.b, 0x99));
	pixel_count = map->floor_image->width * map->floor_image->height;
	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < pixel_count)
	{
		col = ((t_color *)map->floor_image->data)[i];
		r += col.r;
		g += col.g;
		b += col.b;
		i++;
	}
	return (rgba(r / pixel_count, g / pixel_count, b / pixel_count, 0x99));
}

void minimap_create(t_minimap *minimap, t_r3d *r3d, t_map *map, t_alloc_table *at)
{
	rasterizer_init_overlay(&minimap->rast, r3d, (t_rect){{0, 0}, {WIDTH, HEIGHT}}, 70.0, at);
	minimap->map = map;
	minimap->bg = calc_avg_color(map);
}

static void draw_cube(t_minimap *minimap, t_vars *vars, t_v3 pos)
{
	const t_mat4 m = mat4_mul_mat4(mat4_rotation(v3(0, 0, minimap->rast.r3d->camera->rotation.y)), mat4_translation(pos));

	//
	// Top face
	//
	t_tri tri = (t_tri){
		.v0 = v3(-0.5, -0.5, +0.5),
		.v1 = v3(+0.5, -0.5, +0.5),
		.v2 = v3(-0.5, +0.5, +0.5)
	};
	t_tri tri2 = (t_tri){
		.v0 = v3(+0.5, -0.5, +0.5),
		.v1 = v3(+0.5, +0.5, +0.5),
		.v2 = v3(-0.5, +0.5, +0.5)
	};

	tri.v0 = mat4_multiply_v3(m, tri.v0), tri.v1 = mat4_multiply_v3(m, tri.v1), tri.v2 = mat4_multiply_v3(m, tri.v2);
	tri2.v0 = mat4_multiply_v3(m, tri2.v0), tri2.v1 = mat4_multiply_v3(m, tri2.v1), tri2.v2 = mat4_multiply_v3(m, tri2.v2);

	rasterize_triangle(&minimap->rast, tri, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, NULL, hex(0x00222222));

	//
	// -Y face
	//
	t_tri tri3 = (t_tri){
		.v0 = v3(-0.5, -0.5, -0.5),
		.v1 = v3(+0.5, -0.5, -0.5),
		.v2 = v3(-0.5, -0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}
	};
	t_tri tri4 = (t_tri){
		.v0 = v3(+0.5, -0.5, -0.5),
		.v1 = v3(+0.5, -0.5, +0.5),
		.v2 = v3(-0.5, -0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}
	};

	tri3.v0 = mat4_multiply_v3(m, tri3.v0), tri3.v1 = mat4_multiply_v3(m, tri3.v1), tri3.v2 = mat4_multiply_v3(m, tri3.v2);
	tri4.v0 = mat4_multiply_v3(m, tri4.v0), tri4.v1 = mat4_multiply_v3(m, tri4.v1), tri4.v2 = mat4_multiply_v3(m, tri4.v2);

	rasterize_triangle(&minimap->rast, tri3, vars->map->no, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri4, vars->map->no, hex(0x00DDDDDD));

	//
	// +Y face
	//
	t_tri tri5 = (t_tri){
		.v0 = v3(-0.5, +0.5, -0.5),
		.v2 = v3(+0.5, +0.5, -0.5),
		.v1 = v3(-0.5, +0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}
	};
	t_tri tri6 = (t_tri){
		.v0 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(+0.5, +0.5, +0.5),
		.v1 = v3(-0.5, +0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}
	};

	tri5.v0 = mat4_multiply_v3(m, tri5.v0), tri5.v1 = mat4_multiply_v3(m, tri5.v1), tri5.v2 = mat4_multiply_v3(m, tri5.v2);
	tri6.v0 = mat4_multiply_v3(m, tri6.v0), tri6.v1 = mat4_multiply_v3(m, tri6.v1), tri6.v2 = mat4_multiply_v3(m, tri6.v2);

	rasterize_triangle(&minimap->rast, tri5, vars->map->so, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri6, vars->map->so, hex(0x00DDDDDD));

	//
	// +X face
	//
	t_tri tri7 = (t_tri){
		.v0 = v3(+0.5, -0.5, -0.5),
		.v1 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(+0.5, -0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}
	};
	t_tri tri8 = (t_tri){
		.v0 = v3(+0.5, +0.5, -0.5),
		.v1 = v3(+0.5, +0.5, +0.5),
		.v2 = v3(+0.5, -0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}
	};

	tri7.v0 = mat4_multiply_v3(m, tri7.v0),
	tri7.v1 = mat4_multiply_v3(m, tri7.v1),
	tri7.v2 = mat4_multiply_v3(m, tri7.v2);
	tri8.v0 = mat4_multiply_v3(m, tri8.v0),
	tri8.v1 = mat4_multiply_v3(m, tri8.v1),
	tri8.v2 = mat4_multiply_v3(m, tri8.v2);

	rasterize_triangle(&minimap->rast, tri7, vars->map->we, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri8, vars->map->we, hex(0x00DDDDDD));

	//
	// +X face
	//
	t_tri tri9 = (t_tri){
		.v0 = v3(-0.5, -0.5, -0.5),
		.v2 = v3(-0.5, +0.5, -0.5),
		.v1 = v3(-0.5, -0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}
	};
	t_tri tri10 = (t_tri){
		.v0 = v3(-0.5, +0.5, -0.5),
		.v2 = v3(-0.5, +0.5, +0.5),
		.v1 = v3(-0.5, -0.5, +0.5),

		.t0 = (t_v2){1, 0},
		.t2 = (t_v2){1, 1},
		.t1 = (t_v2){0, 1}
	};

	tri9.v0 = mat4_multiply_v3(m, tri9.v0), tri9.v1 = mat4_multiply_v3(m, tri9.v1), tri9.v2 = mat4_multiply_v3(m, tri9.v2);
	tri10.v0 = mat4_multiply_v3(m, tri10.v0), tri10.v1 = mat4_multiply_v3(m, tri10.v1), tri10.v2 = mat4_multiply_v3(m, tri10.v2);

	rasterize_triangle(&minimap->rast, tri9, vars->map->ea, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri10, vars->map->ea, hex(0x00DDDDDD));
}

static void draw_door(t_minimap *minimap, t_vars *vars, t_v3 pos)
{
	const t_mat4 m = mat4_mul_mat4(mat4_rotation(v3(0, 0, minimap->rast.r3d->camera->rotation.y)), mat4_translation(pos));

	//
	// Top face
	//
	t_tri tri = (t_tri){.v0 = v3(-0.5, -0.2, +0.5),
						.v1 = v3(+0.5, -0.2, +0.5),
						.v2 = v3(-0.5, +0.2, +0.5)};
	t_tri tri2 = (t_tri){.v0 = v3(+0.5, -0.2, +0.5),
						.v1 = v3(+0.5, +0.2, +0.5),
						.v2 = v3(-0.5, +0.2, +0.5)};

	tri.v0 = mat4_multiply_v3(m, tri.v0), tri.v1 = mat4_multiply_v3(m, tri.v1),
	tri.v2 = mat4_multiply_v3(m, tri.v2);
	tri2.v0 = mat4_multiply_v3(m, tri2.v0),
	tri2.v1 = mat4_multiply_v3(m, tri2.v1),
	tri2.v2 = mat4_multiply_v3(m, tri2.v2);

	rasterize_triangle(&minimap->rast, tri, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri2, NULL, hex(0x00222222));

	//
	// -Y face
	//
	t_tri tri3 = (t_tri){.v0 = v3(-0.5, -0.2, -0.5),
						.v1 = v3(+0.5, -0.2, -0.5),
						.v2 = v3(-0.5, -0.2, +0.5),

						.t0 = (t_v2){0, 0},
						.t1 = (t_v2){1, 0},
						.t2 = (t_v2){0, 1}};
	t_tri tri4 = (t_tri){.v0 = v3(+0.5, -0.2, -0.5),
						.v1 = v3(+0.5, -0.2, +0.5),
						.v2 = v3(-0.5, -0.2, +0.5),

						.t0 = (t_v2){1, 0},
						.t1 = (t_v2){1, 1},
						.t2 = (t_v2){0, 1}};

	tri3.v0 = mat4_multiply_v3(m, tri3.v0),
	tri3.v1 = mat4_multiply_v3(m, tri3.v1),
	tri3.v2 = mat4_multiply_v3(m, tri3.v2);
	tri4.v0 = mat4_multiply_v3(m, tri4.v0),
	tri4.v1 = mat4_multiply_v3(m, tri4.v1),
	tri4.v2 = mat4_multiply_v3(m, tri4.v2);

	rasterize_triangle(&minimap->rast, tri3, vars->door, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri4, vars->door, hex(0x00222222));

	//
	// +Y face
	//
	t_tri tri5 = (t_tri){.v0 = v3(-0.5, +0.2, -0.5),
						.v2 = v3(+0.5, +0.2, -0.5),
						.v1 = v3(-0.5, +0.2, +0.5),

						.t0 = (t_v2){0, 0},
						.t2 = (t_v2){1, 0},
						.t1 = (t_v2){0, 1}};
	t_tri tri6 = (t_tri){.v0 = v3(+0.5, +0.2, -0.5),
						.v2 = v3(+0.5, +0.2, +0.5),
						.v1 = v3(-0.5, +0.2, +0.5),

						.t0 = (t_v2){1, 0},
						.t2 = (t_v2){1, 1},
						.t1 = (t_v2){0, 1}};

	tri5.v0 = mat4_multiply_v3(m, tri5.v0),
	tri5.v1 = mat4_multiply_v3(m, tri5.v1),
	tri5.v2 = mat4_multiply_v3(m, tri5.v2);
	tri6.v0 = mat4_multiply_v3(m, tri6.v0),
	tri6.v1 = mat4_multiply_v3(m, tri6.v1),
	tri6.v2 = mat4_multiply_v3(m, tri6.v2);

	rasterize_triangle(&minimap->rast, tri5, vars->door, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri6, vars->door, hex(0x00222222));

	//
	// +X face
	//
	t_tri tri7 = (t_tri){.v0 = v3(+0.5, -0.2, -0.5),
						.v1 = v3(+0.5, +0.2, -0.5),
						.v2 = v3(+0.5, -0.2, +0.5)};
	t_tri tri8 = (t_tri){.v0 = v3(+0.5, +0.2, -0.5),
						.v1 = v3(+0.5, +0.2, +0.5),
						.v2 = v3(+0.5, -0.2, +0.5)};

	tri7.v0 = mat4_multiply_v3(m, tri7.v0),
	tri7.v1 = mat4_multiply_v3(m, tri7.v1),
	tri7.v2 = mat4_multiply_v3(m, tri7.v2);
	tri8.v0 = mat4_multiply_v3(m, tri8.v0),
	tri8.v1 = mat4_multiply_v3(m, tri8.v1),
	tri8.v2 = mat4_multiply_v3(m, tri8.v2);

	rasterize_triangle(&minimap->rast, tri7, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri8, NULL, hex(0x00222222));

	//
	// +X face
	//
	t_tri tri9 = (t_tri){.v0 = v3(-0.5, -0.2, -0.5),
						.v2 = v3(-0.5, +0.2, -0.5),
						.v1 = v3(-0.5, -0.2, +0.5)};
	t_tri tri10 = (t_tri){.v0 = v3(-0.5, +0.2, -0.5),
							.v2 = v3(-0.5, +0.2, +0.5),
							.v1 = v3(-0.5, -0.2, +0.5)};

	tri9.v0 = mat4_multiply_v3(m, tri9.v0), tri9.v1 = mat4_multiply_v3(m, tri9.v1), tri9.v2 = mat4_multiply_v3(m, tri9.v2);
	tri10.v0 = mat4_multiply_v3(m, tri10.v0), tri10.v1 = mat4_multiply_v3(m, tri10.v1), tri10.v2 = mat4_multiply_v3(m, tri10.v2);

	rasterize_triangle(&minimap->rast, tri9, NULL, hex(0x00222222));
	rasterize_triangle(&minimap->rast, tri10, NULL, hex(0x00222222));
}

static void	draw_character(t_minimap *minimap, t_v3 pos)
{
	// const t_mat4 m = mat4_mul_mat4(mat4_rotation(v3(0, 0, minimap->rast.r3d->camera->rotation.y)), mat4_translation(pos));
	const t_mat4 m = mat4_translation(pos);

	/*
	       0.0
			^
           / \
	      /   \
		 +-----+
	  -0.5     0.5
	*/

	t_tri tri1 = (t_tri){
		.v0 = v3(+0.0, -0.4, +0.4),
		.v1 = v3(+0.4, +0.4, +0.4),
		.v2 = v3(-0.4, +0.4, +0.4),
	};

	tri1.v0 = mat4_multiply_v3(m, tri1.v0), tri1.v1 = mat4_multiply_v3(m, tri1.v1), tri1.v2 = mat4_multiply_v3(m, tri1.v2);

	rasterize_triangle(&minimap->rast, tri1, NULL, hex(0x00FFFFFF));
}

static void draw_floor(t_minimap *minimap, t_vars *vars, t_v3 pos)
{
	const t_mat4 m = mat4_mul_mat4(mat4_rotation(v3(0, 0, minimap->rast.r3d->camera->rotation.y)), mat4_translation(pos));

	t_tri tri = (t_tri){
		.v0 = v3(-0.5, -0.5, -0.5),
		.v1 = v3(+0.5, -0.5, -0.5),
		.v2 = v3(-0.5, +0.5, -0.5),

		.t0 = (t_v2){0, 0},
		.t1 = (t_v2){1, 0},
		.t2 = (t_v2){0, 1}
	};
	t_tri tri2 = (t_tri){
		.v0 = v3(+0.5, -0.5, -0.5),
		.v1 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(-0.5, +0.5, -0.5),

		.t0 = (t_v2){1, 0},
		.t1 = (t_v2){1, 1},
		.t2 = (t_v2){0, 1}
	};

	tri.v0 = mat4_multiply_v3(m, tri.v0), tri.v1 = mat4_multiply_v3(m, tri.v1), tri.v2 = mat4_multiply_v3(m, tri.v2);
	tri2.v0 = mat4_multiply_v3(m, tri2.v0), tri2.v1 = mat4_multiply_v3(m, tri2.v1), tri2.v2 = mat4_multiply_v3(m, tri2.v2);

	rasterize_triangle(&minimap->rast, tri, vars->map->floor_image, vars->map->floor_color);
	rasterize_triangle(&minimap->rast, tri2, vars->map->floor_image, vars->map->floor_color);
}

t_color blend(t_color fg, t_color bg)
{
	t_color result;
	const unsigned int alpha = (255 - fg.t) + 1;
	const unsigned int inv_alpha = 256 - (255 - fg.t);

	result.r = (unsigned char)((alpha * fg.r + inv_alpha * bg.r) >> 8);
	result.g = (unsigned char)((alpha * fg.g + inv_alpha * bg.g) >> 8);
	result.b = (unsigned char)((alpha * fg.b + inv_alpha * bg.b) >> 8);
	result.t = 0x00;
	return (result);
}

static void draw_background(t_minimap *minimap, t_r3d *r3d, t_rect rect)
{
	int x;
	int y;
	t_color col;

	x = 0;
	while (x < rect.max.x - rect.min.x)
	{
		y = 0;
		while (y < rect.max.y - rect.min.y)
		{
			col = r3d->color_buffer[(rect.min.x + x) + (rect.min.y + y) * r3d->width];
			r3d->color_buffer[(rect.min.x + x) + (rect.min.y + y) * r3d->width] =
				blend(minimap->bg, col);
			y++;
		}
		x++;
	}
}

void minimap_draw(t_minimap *minimap, t_r3d *r3d, t_vars *vars) {
	int x;
	int y;

	rasterizer_clear(&minimap->rast);
	draw_background(minimap, minimap->rast.r3d, minimap->rast.rect);
	x = 0;
	while (x < minimap->map->width)
	{
		y = 0;
		while (y < minimap->map->height)
		{
			if (minimap->map->tiles[x + y * minimap->map->width] != TILE_EMPTY && minimap->map->tiles[x + y * minimap->map->width] != TILE_DOOR)
				draw_cube(minimap, vars, v3_sub(v3(x, y, -8), v3(r3d->camera->position.x - 0.5, r3d->camera->position.z - 0.5, 0)));
			else if (minimap->map->tiles[x + y * minimap->map->width] == TILE_DOOR)
			{
				draw_floor(minimap, vars, v3_sub(v3(x, y, -8), v3(r3d->camera->position.x - 0.5, r3d->camera->position.z - 0.5, 0)));
				draw_door(minimap, vars, v3_sub(v3(x, y, -8), v3(r3d->camera->position.x - 0.5, r3d->camera->position.z - 0.5, 0)));
			}
			else
				draw_floor(minimap, vars, v3_sub(v3(x, y, -8), v3(r3d->camera->position.x - 0.5, r3d->camera->position.z - 0.5, 0)));
			y++;
		}
		x++;
	}
	draw_character(minimap, v3(-0.0, -0.0, -8));
}
