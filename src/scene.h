/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:24:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/23 14:00:18 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "math/v3.h"
# include "mem.h"
# include "render/render.h"
# include "gun.h"
# include <stdbool.h>

/* Entities definition */

typedef struct s_vars	t_vars;

typedef void			(*t_draw_hook)(t_r3d *r3d, void *entity,
	t_camera *camera, t_vars *vars);
typedef void			(*t_tick_hook)(t_vars *vars, void *entity);
typedef void			(*t_free_hook)(t_vars *vars, void *entity);

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
	t_free_hook	free;

	bool		is_dead;

	t_map		*map;
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

t_player		*player_new(t_vars *vars, t_map *map, int id);
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

t_fake_player	*fake_player_new(t_vars *vars, t_map *map, int id, t_alloc_table *at);
t_image			*fake_player_get_image(t_fake_player *fp, t_vars *vars);

#endif
