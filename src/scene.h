/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:24:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/10 23:22:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "math/v3.h"
# include "render/render.h"
# include "gun.h"
#include "sound/sound.h"
# include <stdbool.h>

/* Entities definition */

typedef struct s_scene	t_scene;
typedef struct s_vars	t_vars;

typedef void	(*t_draw_hook)(t_r3d *r3d, void *entity, t_camera *camera, t_vars *vars);
typedef void	(*t_tick_hook)(t_vars *vars, void *entity);

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
}	t_player;

typedef struct s_fake_player
{
	t_entity	base;
	int			health;
}	t_fake_player;

t_player		*player_new(t_vars *vars, t_scene *scene, int id);
t_fake_player	*fake_player_new(t_vars *vars, t_scene *scene, int id);
void		player_mouse_event(int x, int y, t_vars *vars);

typedef struct s_door
{
	t_entity	base;
	float		angle;
	float		target_angle;

	t_v3		initial_pos;
}	t_door;

t_door	*door_new(t_vars *vars, t_scene *scene, int dir, int id);

/* Scene definition */

typedef struct s_scene
{
	t_entity	**entities;
	t_player	*player;
}	t_scene;

t_scene		*create_scene();
void		scene_add_entity(t_scene *scene, void *entity);
void		scene_remove_entity(t_scene *scene, t_entity *entity);
t_entity	*scene_get_entity_by_id(t_scene *scene, int id);

void		draw_scene(t_r3d *r3d, t_scene *scene, t_camera *camera, t_vars *vars);
void		tick_scene(t_vars *vars, t_scene *scene);

void	draw_scene_to_image(t_r3d *r3d, t_scene *scene, t_camera *camera,
	t_image *img);

#endif
