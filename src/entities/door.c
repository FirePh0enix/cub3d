/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:28:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/31 13:11:29 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"

void	door_tick(t_vars *vars, t_door *door);
void	door_draw(t_r3d *r3d, t_door *door, t_camera *camera, t_vars *vars);

t_door	*door_new(t_vars *vars, t_scene *scene, t_mesh *mesh, int id)
{
	t_door	*e;

	(void) vars;
	(void) mesh;
	e = ft_calloc(1, sizeof(t_door));
	if (!e)
		return (NULL);
	e->base.type = ENTITY_DOOR;
	e->base.id = id;
	e->base.tick = (void *) door_tick;
	e->base.draw = (void *) door_draw;
	e->base.transform = (t_transform){};
	e->base.scene = scene;
	e->base.velocity = v3(0, 0, 0);
	e->mesh = mesh;
	return (e);
}

void	door_tick(t_vars *vars, t_door *door)
{
	(void) vars;
	(void) door;
}

void	door_draw(t_r3d *r3d, t_door *door, t_camera *camera, t_vars *vars)
{
	(void) vars;
	r3d_draw_mesh(r3d, door->base.scene, door->mesh, camera, (t_transform){
		v3_add(door->base.transform.position, v3(-1.5, 0, 0)),
		v3_add(door->base.transform.rotation, v3(0, door->angle, 0))
	});
	r3d_draw_mesh(r3d, door->base.scene, door->mesh, camera, (t_transform){
		v3_add(door->base.transform.position, v3(0.0, 0, 0)),
		v3_add(door->base.transform.rotation, v3(0, door->angle, 0))
	});
}
