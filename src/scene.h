/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:24:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/07 20:40:13 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "render/render.h"

/* Entities definition */

typedef struct s_scene	t_scene;

typedef void	(*t_draw_hook)(t_r3d *r3d, void *entity);
typedef void	(*t_tick_hook)(t_r3d *r3d, void *entity);

# define EID_PLAYER     0x10000001
# define EID_SCENE_DOOR 0x10000002

typedef struct s_entity
{
	uint32_t	eid;
	t_draw_hook	draw;
	t_tick_hook	tick;

	t_scene		*scene;
	t_transform	transform;
}	t_entity;

typedef struct s_player
{
	t_entity	base;
	t_camera	*camera;
}	t_player;

t_player	*player_new();

typedef struct s_scene_door
{
	t_entity			base;
	struct s_scene_door	*other_door;
}	t_scene_door;

/* Scene definition */

typedef struct s_scene
{
	t_entity	**entities;
	t_light		*lights;
	t_player	*player;
}	t_scene;

t_scene	*create_scene();
void	scene_add_entity(t_scene *scene, void *entity);

void	draw_scene(t_r3d *r3d, t_scene *scene);
void	tick_scene(t_r3d *r3d, t_scene *scene);

#endif
