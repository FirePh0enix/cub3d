/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:27:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/28 18:56:54 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "math/mat4.h"
# include "math/v2i.h"
# include "math/v3.h"
# include "network/net.h"
# include "render/font.h"
# include "render/render.h"
# include "render/types.h"
# include "scene.h"

# define YELLOW	"\033[0;33m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define RED	"\033[0;31m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define BLACK	"\033[0;30"
# define WHITE	"\033[0;37m"

# include <stdbool.h>

# ifdef _USE_RENDER_THREAD
#  include <pthread.h>
# endif

typedef struct s_map	t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_r3d		*r3d;
	suseconds_t	last_update;

	t_scene		*scene;
	int			entity_id;
	t_map		*map;

	t_panel		*panel;
	t_font		*font;

	t_image		*south;

	bool		*keys;
	bool		buttons[8];

	bool		is_server;
	t_client	client;
	t_server	server;

	float		delta_sec;
	t_v2i		mouse_pos;

	bool		is_focused;

	t_mesh		*enemy_mesh;

#ifdef _USE_RENDER_THREAD
	pthread_t	render_thread;
	bool		running;
#endif
}	t_vars;

inline int	next_entity_id(t_vars *vars)
{
	return (vars->entity_id++);
}

int	key_pressed_hook(int keycode, t_vars *vars);
int	key_released_hook(int keycode, t_vars *vars);
int	mouse_move_hook(int x, int y, t_vars *vars);
int	mouse_button_pressed_hook(int btn, int _i1, int _i2, t_vars *vars);
int	mouse_button_released_hook(int btn, int _i1, int _i2, t_vars *vars);

#define WALL_SIZE 3.0

typedef struct s_wall
{
	t_v3	pos;
	float	w;
	float	h;
	float	rot_y;
	t_mtl	*material;
	t_v3	n;
	bool	hide;

	// Used for ray-casting
	t_v3	p0;
	t_v3	p1;
	t_v3	p2;

	// Used for rasterization
	t_tri	t0;
	t_tri	t1;
}	t_wall;

t_wall	wall(t_v3 position, float rotation_y, t_mtl *mtl);

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
	int			width;
	int			height;

	t_color		floor_color;
	t_color		ceiling_color;

	t_mtl		*no;
	t_mtl		*so;
	t_mtl		*we;
	t_mtl		*ea;

	t_wall2		*walls;
	int			*tiles;

	/*
		POS - v3(x * WALL_SIZE, 0, y * WALL_SIZE)
		ROTATION:
		- N - v3(0, 0, 0)
		- S - v3(0, M_PI, 0)
		- W - v3(0, M_PI / 2, 0)
		- E - v3(0, 3 * M_PI / 2, 0)
	 */
	t_transform	spawns[MAX_CLIENT];
	int			spawn_count;
}	t_map;

void	map_to_tiles(t_map *map, char **maps);
void	bake_map(t_map *map, t_vars *vars);
void	draw_map(t_r3d *r3d, t_map *map);

char	*read_to_string(char *filename);
char	**create_map(char *path, t_map *map);
bool	is_map_surrounded(char **maps, t_map *map);
char	**fill_map_with_space(char **map, size_t width, size_t height);
void	find_player_pos(char **maps, t_map *map);
int		calc_map_height(char **maps);
int		calc_map_max_width(char **maps);
bool	fill_texture(t_map *map, char *maps);
char	**create_textures(char *map);
char	*detect_texture_path(char *path);
t_image	*load_texture(char *textures, char *identifier);
char	*detect_identifier(char *texture);
bool 	is_valid_identifier(char *str);
bool create_material(char *identifier, t_map *map, t_image	*image);
bool check_all_materials(t_map *map);
#endif
