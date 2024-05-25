/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/24 13:22:48 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../math/vec.h"
# include "../math/matrix.h"
# include "types.h"
# include "../gui/gui.h"
# include "font.h"
# include "mlx_int.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define WALL_RENDER_DISTANCE    25.0

typedef struct s_vars	t_vars;
typedef struct s_scene	t_scene;
typedef struct s_r3d	t_r3d;

typedef struct s_tri
{
	t_v3	v0;
	t_v3	v1;
	t_v3	v2;

	t_v2	t0;
	t_v2	t1;
	t_v2	t2;

	t_v3	n0;
	t_v3	n1;
	t_v3	n2;
}	t_tri;

typedef struct s_image
{
	uint32_t	*data;
	int			width;
	int			height;
	uint8_t		bpp;
}	t_image;

t_image	*tga_load_from_file(char *filename);
t_image	*tga_create(int width, int height);

typedef struct s_mtl
{
	char	*name;
	t_image	*image;
}	t_mtl;

t_mtl	*mtl_load_from_file(t_vars *vars, char *filename);
t_mtl	*mtl_new(char *name, t_image *image);

typedef struct s_face
{
	int	v[3];
	int	t[3];
	int	n[3];
}	t_face;

typedef struct s_mesh
{
	t_mtl	*material;

	t_face	*faces;
	size_t	faces_count;

	t_v3	*vertices;
	size_t	vertices_count;

	t_v2	*textures;
	size_t	textures_count;

	t_v3	*normals;
	size_t	normals_count;
}	t_mesh;

/*
 * Load a Wavefront OBJ file and its associated mtl files into an usable mesh.
 */
t_mesh	*mesh_load_from_obj(t_vars *vars, char *filename);

/*
 * Validate indices for the mesh data. This means that indices can be used to
 * index the mesh data without any check without risking Out of Bounds.
 *
 * TODO
 */
bool	mesh_validate(t_mesh *mesh);

typedef enum e_light_type
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
}	t_light_type;

/*
 * A light, either a directional light (like sunlight) or a point light (every
 * light ray come from the same position).
 */
typedef struct s_light
{
	t_light_type	type;
	t_v3			position;
	float			intensity;
	t_v3			direction;
	t_color			color;
}	t_light;

float	light_intensity(t_v3 light_dir, t_v3 n);
t_v3	compute_lighting(t_r3d *r3d, t_light *lights, t_v3 pos, t_v3 n);

typedef struct s_framebuffer
{
	float		*depth;
	t_color		*color;
	int			width;
	int			height;
}	t_framebuffer;

typedef struct s_camera
{
	t_v3			position;
	t_v3			rotation;
	t_scene			*scene;

	t_framebuffer	*fb;
}	t_camera;

typedef enum e_mode
{
	MODE_NORMAL,
	MODE_WIREFRAME,
	MODE_DEPTH,
}	t_mode;

t_framebuffer	*create_fb(int width, int height);
void			fb_clear_depth_buffer(t_framebuffer *fb);
void			fb_clear_color_buffer(t_framebuffer *fb, t_color color);

typedef struct s_r3d
{
	t_img			*canvas;
	t_mode			mode;

	float			fov;

	int				width;
	int				height;

	t_framebuffer	*fb;
	t_camera		*camera;

	t_mat4			projection_matrix;
	float			rot_z;

	/* Pre-computed values to speed up calculation */
	float			tan2_fov;
	float			aspect_ratio;
}	t_r3d;

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
void	r3d_clear_depth_buffer(t_r3d *r3d);
void	r3d_clear_color_buffer(t_r3d *r3d, t_color color);

int		r3d_key_hook(int keycode, t_r3d *r3d);

void	r3d_draw_triangle(t_r3d *r3d, t_camera *camera, t_tri tri, t_transform transform, t_mtl *material);

void	r3d_draw_mesh(t_r3d *r3d, t_scene *scene, t_mesh *mesh,
	t_camera *camera, t_transform transform);
void	r3d_fill_triangle(t_r3d *r3d, t_v3 pos, t_tri tri, t_mtl *mtl,
	t_framebuffer *fb, t_light *lights);

typedef struct s_wall	t_wall;
typedef struct s_map	t_map;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}	t_ray;

typedef struct s_ray_result
{
	float	distance;
	t_v3	uv;
}	t_ray_result;

/*
	Draw a wall using ray-casting.
 */
void	r3d_raycast_wall(t_r3d *r3d, t_wall *wall, t_light *lights, t_v2i min, t_v2i max);
void	r3d_draw_wall(t_r3d *r3d, t_wall *wall, t_light *lights);

void	r3d_draw_walls(t_r3d *r3d, t_map *map);

void	r3d_draw_gui(t_r3d *r3d, t_panel *panel);
void	r3d_draw_text(t_r3d *r3d, t_font *font, char *text, t_v2 pos);

#endif
