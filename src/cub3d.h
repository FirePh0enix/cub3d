/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:27:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/23 14:12:32 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "math/mat4.h"
# include "network/net.h"
# include "render/font.h"
# include "render/render.h"
# include "scene.h"
#include <stdbool.h>

typedef struct s_map	t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_r3d		*r3d;
	suseconds_t	last_update;

	t_scene		*scene;
	t_map		*map;

	t_panel		*panel;
	t_font		*font;

	t_image		*south;

	bool		*keys;

	bool		is_server;
	t_client	client;
	t_server	server;
}	t_vars;

int	key_pressed_hook(int keycode, t_vars *vars);
int key_released_hook(int keycode, t_vars *vars);

#define WALL_SIZE 3.0

typedef struct s_wall
{
	t_v3	pos;
	float	w;
	float	h;
	float	rot_y;
	t_image	*img;
	t_v3	n;

	t_mat4	rotation;
	t_mat4	inverse_rotation;

	t_mat4	position;
	t_mat4	inverse_position;
}	t_wall;

t_wall	wall(t_v3 position, float rotation_y, t_image *img);

typedef struct s_wall2
{
	t_wall	no;
	t_wall	so;
	t_wall	we;
	t_wall	ea;

	bool	is_empty;
}	t_wall2;

enum e_tile
{
	TILE_EMPTY,
	TILE_FULL
};

typedef struct s_map
{
	int		width;
	int		height;

	t_color	floor_color;
	t_color	ceiling_color;

	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*ea;

	t_wall2	*walls;
	int		*tiles;
}	t_map;

void	map_to_tiles(t_map *map, char **maps);
void	bake_map(t_map *map, t_vars *vars);
void	draw_map(t_r3d *r3d, t_map *map);

char	*read_to_string(char *filename);
char	**create_map(char *path, t_map *map);
bool	is_map_surrounded(char **maps, t_map *map);
char	**fill_map_with_space(char **map, size_t width, size_t height);
int		calc_map_height(char **maps);
int		calc_map_max_width(char **maps);
#endif
