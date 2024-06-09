/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 23:06:43 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"
# include "../gui/gui.h"
# include "font.h"
# include "mlx_int.h"
# include <stdbool.h>
# include <stdint.h>

typedef struct s_map	t_map;
typedef struct s_scene	t_scene;

typedef struct s_image
{
	uint32_t	*data;
	int			width;
	int			height;
	uint8_t		bpp;
}	t_image;

t_image	*tga_load_from_file(char *filename);
t_image	*tga_create(int width, int height);

typedef struct s_camera
{
	t_v3			position;
	t_v3			rotation;
	t_scene			*scene;

	float			plane_x;
	float			plane_y;

	float			dir_x;
	float			dir_y;
}	t_camera;

typedef enum e_mode
{
	MODE_NORMAL,
	MODE_DEPTH,
}	t_mode;

typedef struct s_r3d
{
	t_img			*canvas;

	float			fov;

	int				width;
	int				height;

	t_camera		*camera;

	t_color			*color_buffer;
	float			*depth_buffer;

	t_mode			mode;
}	t_r3d;

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
void	r3d_clear_depth_buffer(t_r3d *r3d);
void	r3d_clear_color_buffer(t_r3d *r3d, t_color color);

int		r3d_key_hook(int keycode, t_r3d *r3d);

/*
	GUI rendering
 */

void	r3d_draw_gui(t_r3d *r3d, t_panel *panel);
float	r3d_get_text_size(t_r3d *r3d, t_font *font, char *text);

/*
	Raycasting
 */

void	r3d_raycast_world(t_r3d *r3d, t_map *map, t_vars *vars);

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

t_sprite	sprite_create(t_image *image);
t_sprite	sprite_create_anim(t_image **images, int num, bool loop, suseconds_t ms);

t_image		*sprite_get_image(t_sprite *sprite);
void		sprite_tick(t_sprite *sprite);
bool		sprite_is_end(t_sprite *sprite);

void		sprite_draw(t_r3d *r3d, t_sprite *sprite, t_v2i pos, float scale);
void		sprite_draw_single(t_r3d *r3d, t_image *image, t_v2i pos, float scale);

/*
	Minimap
 */

typedef struct s_minimap
{
	t_image	*background;
}	t_minimap;

void	minimap_create(t_minimap *minimap, t_map *map);
void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_v2i pos, t_v2i size);

#endif
