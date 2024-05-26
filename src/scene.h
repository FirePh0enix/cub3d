/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phoenix <phoenix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:24:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/27 00:25:21 by phoenix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "render/render.h"

/* Entities definition */

typedef struct s_scene	t_scene;

typedef void	(*t_draw_hook)(t_r3d *r3d, void *entity, t_camera *camera, t_vars *vars);
typedef void	(*t_tick_hook)(t_vars *vars, void *entity);

# define EID_PLAYER     0x10000001
# define EID_SCENE_DOOR 0x10000002
# define EID_MESH_INST  0x10000003

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
	int			mouse_x;
	int			mouse_y;
}	t_player;

t_player	*player_new(t_vars *vars, t_scene *scene);
void		player_mouse_event(int x, int y, t_vars *vars);

typedef struct s_mesh_inst
{
	t_entity	base;
	t_mesh		*mesh;
}	t_mesh_inst;

t_mesh_inst	*mesh_inst_new(t_vars *vars, t_scene *scene, t_mesh *mesh);

/* Scene definition */

typedef struct s_scene
{
	t_entity	**entities;
	t_light		*lights;
	t_player	*player;
}	t_scene;

t_scene	*create_scene();
void	scene_add_entity(t_scene *scene, void *entity);

void	draw_scene(t_r3d *r3d, t_scene *scene, t_camera *camera, t_vars *vars);
void	tick_scene(t_vars *vars, t_scene *scene);

void	draw_scene_to_image(t_r3d *r3d, t_scene *scene, t_camera *camera,
	t_image *img);

#endif
