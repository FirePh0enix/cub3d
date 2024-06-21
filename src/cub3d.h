#ifndef CUB3D_H
# define CUB3D_H

#include "mem.h"
#include <stddef.h>
# ifndef _BONUS
#  define _BONUS 0
# endif

# include "gun.h"
# include "math/mat4.h"
# include "math/v2i.h"
# include "math/v3.h"
# include "network/net.h"
# include "render/font.h"
# include "render/render.h"
# include "render/types.h"
# include "scene.h"
# include "menu.h"
# include "minimap.h"

# include <stdbool.h>

# include "./parsing/parsing.h"

typedef struct s_map	t_map;

typedef struct s_scoreboard_entry
{
	char	username[MAX_CLIENT_NAME];
	int		present;
	int		kills;
	int		death;
}	t_scoreboard_entry;

typedef struct s_scoreboard
{
	t_scoreboard_entry	entries[MAX_CLIENT + 1];
}	t_scoreboard;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_r3d			*r3d;
	suseconds_t		last_update;

	t_scene			*scene;
	int				entity_id;
	t_map			*map;

	t_font			*font;
	t_menu			menu;
	bool			menu_open;

	bool			*keys;
	bool			buttons[8];

	bool			is_server;
	t_client		client;
	t_server		server;

	float			delta_sec;
	t_v2i			mouse_pos;

	bool			is_focused;

	t_scoreboard	scoreboard;
	t_minimap		minimap;

	t_gun			shotgun;

	t_sprite		player_sprite;
	t_image			*door;
}	t_vars;

inline int	next_entity_id(t_vars *vars)
{
	return (vars->entity_id++);
}

suseconds_t	getms(void);

int	key_pressed_hook(int keycode, t_vars *vars);
int	key_released_hook(int keycode, t_vars *vars);
int	mouse_move_hook(int x, int y, t_vars *vars);
int	mouse_button_pressed_hook(int btn, int _i1, int _i2, t_vars *vars);
int	mouse_button_released_hook(int btn, int _i1, int _i2, t_vars *vars);

#define WALL_SIZE 1.0

enum e_tile
{
	TILE_EMPTY,
	TILE_DOOR,

	TILE_FULL = 2,
	TILE_2 = 3,
	TILE_3,
	TILE_4,
	TILE_5,
	TILE_6,
	TILE_7,
	TILE_8,
	TILE_9,
};

typedef struct s_map
{
	int			width;
	int			height;

	t_color		floor_color;
	t_color		ceiling_color;

	t_image		*no;
	t_image		*so;
	t_image		*we;
	t_image		*ea;

	t_image		*floor_image;
	t_image		*ceilling_image;

	int			*tiles;
	t_transform	spawns[MAX_CLIENT];
	int			spawn_count;
	char		**maps;
	char		**map_config;
}	t_map;

typedef struct s_box
{
	t_v3 min;
	t_v3 max;
}	t_box;

char	*_get_file_data(char *filename);
size_t	_get_file_size(char *filename);
char	*read_file(char *filename, t_alloc_table *at);

t_image	**load_images(t_alloc_table *at ,int num, ...);

void	draw_map(t_r3d *r3d, t_map *map);
t_entity	*raycast_entity(t_map *map, t_scene *scene, t_transform ray, float size, uint32_t entity_type);

//############################################################################//
								// BOUNDARY BOX//
//############################################################################//
t_box	box_from_entity(t_entity *entity);
t_box	box_from_velocity_x(t_entity *entity, float delta);
t_box	box_from_velocity_y(t_entity *entity, float delta);
t_box	box_from_velocity_z(t_entity *entity, float delta);
t_box	box_from_wall(int x, int y);

//############################################################################//
								// COLLISION //
//############################################################################//
bool	collide_aabb_vs_aabb(t_box a, t_box b);
bool	collide_point_vs_aabb(t_v3 point, t_box b);
bool	collide_wall(t_box player, int x, int y);
bool 	collide_map(t_box player, t_map *map);
bool 	collide_entities(t_entity **entities, t_box player);

//############################################################################//
								// VELOCITY //
//############################################################################//
void	adjust_vel(t_player *player, t_map *map, float delta, t_entity **ent);

//############################################################################//
								// FREE MEMORY //
//############################################################################//
void	ft_free(t_vars *vars, t_alloc_table *at);

//############################################################################//
								// PARSING //
//############################################################################//
bool	parsing(t_vars *vars, char **argv, t_alloc_table *at);

#endif
