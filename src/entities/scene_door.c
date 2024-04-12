/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:57:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/12 23:28:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"

void	scene_door_draw(t_r3d *r3d, t_scene_door *door, t_camera *camera);
void	scene_door_tick(t_vars *vars, t_scene_door *door);

t_mtl	*create_mtl(float scale_x, float scale_y)
{
	t_mtl	*mtl;

	mtl = malloc(sizeof(t_mtl));
	mtl->name = "";
	mtl->image = malloc(sizeof(t_image));
	mtl->image->width = 720 * scale_x;
	mtl->image->height = 720 * scale_y;
	mtl->image->data = malloc(sizeof(uint32_t) * mtl->image->width
		* mtl->image->height);
	return (mtl);
}

t_scene_door	*scene_door_new(t_vars *vars, t_scene *scene)
{
	t_scene_door	*scene_door;

	scene_door = ft_calloc(1, sizeof(t_scene_door));
	scene_door->base.eid = EID_SCENE_DOOR;
	scene_door->base.draw = (void *) scene_door_draw;
	scene_door->base.tick = (void *) scene_door_tick;
	scene_door->base.scene = scene;
	scene_door->fb = create_fb(1280, 720);
	scene_door->mesh = mesh_load_from_obj(vars, "models/scene_door.obj");
	scene_door->mesh->material = create_mtl(1.0, 1.0);
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
	for (int x = 280; x < 1000; x++)
		for (int y = 0; y < 720; y++)
		{
			t_color	*buf = (t_color *) door->mesh->material->image->data;
			int		w = door->mesh->material->image->width;
			buf[(x - 280) + y * w] = door->fb->color[x + y * door->fb->width];
		}
	r3d_draw_mesh(r3d, door->base.scene, door->mesh, camera, door->base.transform);
}

void	scene_door_tick(t_vars *vars, t_scene_door *door)
{
	if (!door->base.scene->player)
		return ;
	tick_scene(vars, door->other_door->base.scene);
}
