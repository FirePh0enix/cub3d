/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phoenix <phoenix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:28:12 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 13:01:28 by phoenix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"
#include "../math/utils.h"

void	door_tick(t_vars *vars, t_door *door);
void	door_draw(t_r3d *r3d, t_door *door, t_camera *camera, t_vars *vars);

t_door	*door_new(t_vars *vars, t_scene *scene, int dir, int id)
{
	t_door	*e;

	(void) vars;
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
	e->base.width = 3.0;
	e->base.depth = 1.0;
	e->base.height = 3.0;
	e->angle = 0;
	return (e);
}

void	door_tick(t_vars *vars, t_door *door)
{
	(void) vars;
	(void) door;

	if (door->initial_pos.x == 0 && door->initial_pos.y == 0 && door->initial_pos.z == 0)
	{
		door->initial_pos = door->base.transform.position;
	}

	if (door->target_angle == 90.0)
	{
		door->base.transform.position.y = lerpf(door->base.transform.position.y, door->initial_pos.y + 3.0, 0.05);
		door->angle = lerpf(door->angle, M_PI, 0.05);
	}
	else
	{
		door->base.transform.position.y = lerpf(door->base.transform.position.y, door->initial_pos.y, 0.05);
		door->angle = lerpf(door->angle, 0, 0.05);
	}
}

void	door_draw(t_r3d *r3d, t_door *door, t_camera *camera, t_vars *vars)
{
	(void) vars;
	// r3d_draw_mesh(r3d, door->base.scene, door->mesh, camera, (t_transform){
	// 	v3_add(door->base.transform.position, v3(1.5, 0, 0)),
	// 	v3_add(door->base.transform.rotation, v3(0, door->angle + M_PI, 0))
	// });
}
