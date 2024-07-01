/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 19:59:49 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"
# include "font.h"
# include "../mem.h"
# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdint.h>

typedef struct	s_img
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img;


typedef struct s_map	t_map;

typedef struct s_tga_hdr
{
	uint8_t		magic;
	uint8_t		colormap;
	uint8_t		encoding;
	uint16_t	cmaporig;
	uint16_t	cmaplen;
	uint8_t		cmapent;
	uint16_t	x;
	uint16_t	y;
	uint16_t	w;
	uint16_t	h;
	uint8_t		bpp;
	uint8_t		pixel_type;
} __attribute__((packed))	t_tga_hdr;

typedef uint8_t			t_rgb[3];

typedef struct s_image
{
	t_color		*data;
	int			w;
	int			h;
	uint8_t		bpp;
}	t_image;

t_image		*tga_load_from_file(char *filename, t_alloc_table *at);
t_image		*tga_create(int width, int height, t_alloc_table *at);
void		image_destroy(t_image *image);

void		read_pixels_nomap_32(t_image *image, char *buf, size_t len);
void		read_pixels_nomap_24(t_image *image, char *buf, size_t len);
void		read_pixels_map_32(t_image *image, t_tga_hdr *hdr, char *buf,
				size_t len);
void		read_pixels_map_24(t_image *image, t_tga_hdr *hdr, char *buf,
				size_t len);
void		read_pixels_gray_8(t_image *image, char *buf, size_t len);

typedef struct s_camera
{
	t_v3			pos;
	t_v3			rot;
	t_map			*map;

	float			plane_x;
	float			plane_y;

	float			dir_x;
	float			dir_y;
}	t_camera;

typedef struct s_r3d
{
	t_img			*canvas;

	float			fov;

	int				w;
	int				h;

	t_camera		*camera;

	t_color			*color;
	float			*depth;
}	t_r3d;

void		r3d_init(t_r3d *r3d, void *mlx, t_v2i size, t_alloc_table *at);
void		r3d_clear_depth_buffer(t_r3d *r3d);
void		r3d_clear_color_buffer(t_r3d *r3d, t_color color);

/*
	GUI rendering
 */

float		r3d_get_text_size(t_r3d *r3d, t_font *font, char *text);

/*
	Raycasting
 */

typedef struct s_cf_param
{
	t_image	*img;
	t_color	col;
	t_v2i	cell;
	t_v2	floor;
	t_v2i	p;
}	t_cf_param;

typedef struct s_cf2_param
{
	t_v2	ray_dir0;
	t_v2	ray_dir1;
	int		y;
}	t_cf2_param;

typedef struct s_ep_param
{
	int		side;
	double	perp_wall_dist;
	double	ray_dir_x;
	double	ray_dir_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		x;
}	t_ep_param;

typedef struct s_re_param
{
	t_v2	t;
	int		ssx;
	t_v2i	sx;
}	t_re_param;

typedef struct s_dl_param
{
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		x;
}	t_dl_param;

typedef struct s_rw_param
{
	t_v2i	map_pos;
	t_v2	dd;
	t_v2	ray_dir;
	int		x;
}	t_rw_param;

void		r3d_raycast_world(t_r3d *r3d, t_map *map, t_vars *vars);
void		raycast_entities(t_r3d *r3d, t_vars *vars);
t_image		*texture_for_wall(t_vars *vars, int side, t_v2i p, t_v2i t);
void		raycast_floor_and_ceiling(t_r3d *r3d, t_map *map);
void		draw_each_pixels(t_r3d *r3d, t_image *texture, t_ep_param p);

/*
	HUD sprite rendering
 */

typedef struct s_sprite
{
	t_image		**images;
	int			current_frame;
	int			num_frames;

	suseconds_t	last_frame_tick;
	suseconds_t	ms;

	bool		loop;
}	t_sprite;

t_sprite	sprite_create(t_image *image, t_alloc_table *at);
t_sprite	sprite_create_anim(t_image **images, int num, bool loop,
				suseconds_t ms);

t_image		*sprite_get_image(t_sprite *sprite);
void		sprite_tick(t_sprite *sprite);
bool		sprite_is_end(t_sprite *sprite);

void		sprite_draw(t_r3d *r3d, t_sprite *sprite, t_v2i pos, float scale);
void		sprite_draw_single(t_r3d *r3d, t_image *image, t_v2i pos,
				float scale);

#endif
