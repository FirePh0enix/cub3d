/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 13:35:51 by ledelbec         ###   ########.fr       */
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

typedef struct s_vars	t_vars;
typedef struct s_scene	t_scene;
typedef struct s_r3d	t_r3d;

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

void	r3d_draw_gui(t_r3d *r3d, t_panel *panel);
void	r3d_draw_text(t_r3d *r3d, t_font *font, char *text, t_v2 pos);
float	r3d_get_text_size(t_r3d *r3d, t_font *font, char *text);

void	r3d_raycast_world(t_r3d *r3d, t_map *map);

typedef struct s_minimap
{
	t_image	*background;
}	t_minimap;

void	minimap_create(t_minimap *minimap, t_map *map);
void	minimap_draw(t_minimap *minimap, t_r3d *r3d, t_v2i pos, t_v2i size);

#endif
