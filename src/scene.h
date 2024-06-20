/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:24:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 17:19:28 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "math/v3.h"
#include "mem.h"
# include "render/render.h"
# include "gun.h"
# include "sound/sound.h"
# include <stdbool.h>

/* Entities definition */

typedef struct s_scene	t_scene;
typedef struct s_vars	t_vars;

typedef void			(*t_draw_hook)(t_r3d *r3d, void *entity,
	t_camera *camera, t_vars *vars);
typedef void			(*t_tick_hook)(t_vars *vars, void *entity);

enum e_type
{
	ENTITY_PLAYER,
	ENTITY_FAKE_PLAYER
};

typedef struct s_entity
{
	uint32_t	type;
	int			id;
	float		width;
	float		height;
	float		depth;
	t_draw_hook	draw;
	t_tick_hook	tick;

	bool		is_dead;

	t_scene		*scene;
	t_transform	transform;

	t_v3		velocity;
}	t_entity;

typedef struct s_player
{
	t_entity	base;
	t_camera	*camera;
	bool		has_jump;
	bool		has_open_door;

	t_gun		gun;
	int			health;
}	t_player;

t_player		*player_new(t_vars *vars, t_scene *scene, int id);
void			player_mouse_event(int x, int y, t_vars *vars);

# define FORW   0
# define FORW_L 1
# define LEFT   2
# define BACK_L 3
# define BACK   4
# define BACK_R 5
# define RIGHT  6
# define FORW_R 7

typedef struct s_fake_player
{
	t_entity	base;
	int			health;

	t_sprite	sp[8];
}	t_fake_player;

t_fake_player	*fake_player_new(t_vars *vars, t_scene *scene, int id);
t_image			*fake_player_get_image(t_fake_player *fp, t_vars *vars);

/* Scene definition */

typedef struct s_scene
{
	t_entity	**entities;
	t_player	*player;
}	t_scene;

t_scene			*create_scene(void);
void			scene_add_entity(t_scene *scene, void *entity, t_alloc_table *at);
void			scene_remove_entity(t_scene *scene, t_entity *entity);
t_entity		*scene_get_entity_by_id(t_scene *scene, int id);
void			destroy_scene(t_scene *scene);

void			draw_scene(t_r3d *r3d, t_scene *scene,
					t_camera *camera, t_vars *vars);
void			tick_scene(t_vars *vars, t_scene *scene);

void			draw_scene_to_image(t_r3d *r3d, t_scene *scene,
					t_camera *camera, t_image *img);

#endif
