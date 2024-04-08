/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:57:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 16:21:08 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"

void	scene_door_draw(t_r3d *r3d, t_scene_door *door, t_camera *camera);
void	scene_door_tick(t_r3d *r3d, t_scene_door *door);

t_scene_door	*scene_door_new(t_vars *vars, t_scene *scene)
{
	t_scene_door	*scene_door;

	scene_door = ft_calloc(1, sizeof(t_scene_door));
	scene_door->base.eid = EID_SCENE_DOOR;
	scene_door->base.draw = (void *) scene_door_draw;
	scene_door->base.tick = (void *) scene_door_tick;
	scene_door->base.scene = scene;
	scene_door->fb = create_fb(1920, 1920);
	scene_door->mesh = mesh_load_from_obj(vars, "models/scene_door.obj");
	scene_door->mesh->material = ft_calloc(1, sizeof(t_mtl));
	scene_door->mesh->material->name = "";
	scene_door->mesh->material->image = ft_calloc(1, sizeof(t_image));
	scene_door->mesh->material->image->data = (void *) scene_door->fb->color;
	scene_door->mesh->material->image->width = scene_door->fb->width;
	scene_door->mesh->material->image->height = scene_door->fb->height;
	return (scene_door);
}

void	scene_door_draw(t_r3d *r3d, t_scene_door *door, t_camera *camera)
{
	if (!door->base.scene->player)
		return ;
	camera->fb = door->fb;
	fb_clear_depth_buffer(door->fb);
	fb_clear_color_buffer(door->fb, hex(0x0));
	draw_scene(r3d, door->other_door->base.scene, camera);
	camera->fb = NULL;
	r3d_draw_mesh(r3d, door->base.scene, door->mesh, camera, door->base.transform);
}

void	scene_door_tick(t_r3d *r3d, t_scene_door *door)
{
	if (!door->base.scene->player)
		return ;
	tick_scene(r3d, door->other_door->base.scene);
}
