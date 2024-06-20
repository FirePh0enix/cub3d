#include "minimap.h"
#include "math/mat4.h"
#include "math/mat4_init.h"
#include "math/mat4_rot.h"
#include "rasterizer/rasterizer.h"
#include "render/render.h"
#include "cub3d.h"
#include <stdio.h>

#define WIDTH 300
#define HEIGHT 300
#define BORDER_WIDTH 6
#define CAM_WIDTH 10

void	minimap_create(t_minimap *minimap, t_r3d *r3d, t_map *map)
{
	rasterizer_init_overlay(&minimap->rast, r3d, (t_rect){
		{0, 0}, {WIDTH, HEIGHT}
	}, 70.0);
	minimap->map = map;
}

static void	draw_cube(t_minimap *minimap, t_v3 pos)
{
	const t_mat4	m = mat4_mul_mat4(mat4_rotation(v3(0, 0, minimap->rast.r3d->camera->rotation.y)), mat4_translation(pos));

	//
	// Top face
	//
	t_tri	tri = (t_tri){
		.v0 = v3(-0.5, -0.5, +0.5),
		.v1 = v3(+0.5, -0.5, +0.5),
		.v2 = v3(-0.5, +0.5, +0.5)
	};
	t_tri	tri2 = (t_tri){
		.v0 = v3(+0.5, -0.5, +0.5),
		.v1 = v3(+0.5, +0.5, +0.5),
		.v2 = v3(-0.5, +0.5, +0.5)
	};

	tri.v0 = mat4_multiply_v3(m, tri.v0), tri.v1 = mat4_multiply_v3(m, tri.v1), tri.v2 = mat4_multiply_v3(m, tri.v2);
	tri2.v0 = mat4_multiply_v3(m, tri2.v0), tri2.v1 = mat4_multiply_v3(m, tri2.v1), tri2.v2 = mat4_multiply_v3(m, tri2.v2);

	rasterize_triangle(&minimap->rast, tri, hex(0x00FFFFFF));
	rasterize_triangle(&minimap->rast, tri2, hex(0x00FFFFFF));

	//
	// -Y face
	//
	t_tri	tri3 = (t_tri){
		.v0 = v3(-0.5, -0.5, -0.5),
		.v1 = v3(+0.5, -0.5, -0.5),
		.v2 = v3(-0.5, -0.5, +0.5)
	};
	t_tri	tri4 = (t_tri){
		.v0 = v3(+0.5, -0.5, -0.5),
		.v1 = v3(+0.5, -0.5, +0.5),
		.v2 = v3(-0.5, -0.5, +0.5)
	};

	tri3.v0 = mat4_multiply_v3(m, tri3.v0), tri3.v1 = mat4_multiply_v3(m, tri3.v1), tri3.v2 = mat4_multiply_v3(m, tri3.v2);
	tri4.v0 = mat4_multiply_v3(m, tri4.v0), tri4.v1 = mat4_multiply_v3(m, tri4.v1), tri4.v2 = mat4_multiply_v3(m, tri4.v2);

	rasterize_triangle(&minimap->rast, tri3, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri4, hex(0x00DDDDDD));

	//
	// +Y face
	//
	t_tri	tri5 = (t_tri){
		.v0 = v3(-0.5, +0.5, -0.5),
		.v2 = v3(+0.5, +0.5, -0.5),
		.v1 = v3(-0.5, +0.5, +0.5)
	};
	t_tri	tri6 = (t_tri){
		.v0 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(+0.5, +0.5, +0.5),
		.v1 = v3(-0.5, +0.5, +0.5)
	};

	tri5.v0 = mat4_multiply_v3(m, tri5.v0), tri5.v1 = mat4_multiply_v3(m, tri5.v1), tri5.v2 = mat4_multiply_v3(m, tri5.v2);
	tri6.v0 = mat4_multiply_v3(m, tri6.v0), tri6.v1 = mat4_multiply_v3(m, tri6.v1), tri6.v2 = mat4_multiply_v3(m, tri6.v2);

	rasterize_triangle(&minimap->rast, tri5, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri6, hex(0x00DDDDDD));

	//
	// +X face
	//
	t_tri	tri7 = (t_tri){
		.v0 = v3(+0.5, -0.5, -0.5),
		.v1 = v3(+0.5, +0.5, -0.5),
		.v2 = v3(+0.5, -0.5, +0.5)
	};
	t_tri	tri8 = (t_tri){
		.v0 = v3(+0.5, +0.5, -0.5),
		.v1 = v3(+0.5, +0.5, +0.5),
		.v2 = v3(+0.5, -0.5, +0.5)
	};

	tri7.v0 = mat4_multiply_v3(m, tri7.v0), tri7.v1 = mat4_multiply_v3(m, tri7.v1), tri7.v2 = mat4_multiply_v3(m, tri7.v2);
	tri8.v0 = mat4_multiply_v3(m, tri8.v0), tri8.v1 = mat4_multiply_v3(m, tri8.v1), tri8.v2 = mat4_multiply_v3(m, tri8.v2);

	rasterize_triangle(&minimap->rast, tri7, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri8, hex(0x00DDDDDD));

	//
	// +X face
	//
	t_tri	tri9 = (t_tri){
		.v0 = v3(-0.5, -0.5, -0.5),
		.v2 = v3(-0.5, +0.5, -0.5),
		.v1 = v3(-0.5, -0.5, +0.5)
	};
	t_tri	tri10 = (t_tri){
		.v0 = v3(-0.5, +0.5, -0.5),
		.v2 = v3(-0.5, +0.5, +0.5),
		.v1 = v3(-0.5, -0.5, +0.5)
	};

	tri9.v0 = mat4_multiply_v3(m, tri9.v0), tri9.v1 = mat4_multiply_v3(m, tri9.v1), tri9.v2 = mat4_multiply_v3(m, tri9.v2);
	tri10.v0 = mat4_multiply_v3(m, tri10.v0), tri10.v1 = mat4_multiply_v3(m, tri10.v1), tri10.v2 = mat4_multiply_v3(m, tri10.v2);

	rasterize_triangle(&minimap->rast, tri9, hex(0x00DDDDDD));
	rasterize_triangle(&minimap->rast, tri10, hex(0x00DDDDDD));
}

void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_v2i pos, t_v2i mappos)
{
	int	x;
	int	y;

	rasterizer_clear(&minimap->rast);

	x = 0;
	while (x < minimap->map->width)
	{
		y = 0;
		while (y < minimap->map->height)
		{
			if (minimap->map->tiles[x + y * minimap->map->width] != TILE_EMPTY)
				draw_cube(minimap, v3_sub(v3(x, y, -8), v3(r3d->camera->position.x, r3d->camera->position.z, 0)));
			y++;
		}
		x++;
	}
}
