/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_inst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:27:58 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 13:51:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"

void	mesh_inst_draw(t_r3d *r3d, t_mesh_inst *mesh_inst, t_camera *camera);

t_mesh_inst	*mesh_inst_new(t_vars *vars, t_scene *scene, t_mesh *mesh)
{
	t_mesh_inst	*mesh_inst;

	(void) vars;
	mesh_inst = ft_calloc(1, sizeof(t_mesh_inst));
	mesh_inst->base.eid = EID_MESH_INST;
	mesh_inst->base.scene = scene;
	mesh_inst->base.draw = (void *) mesh_inst_draw;
	mesh_inst->mesh = mesh;
	return (mesh_inst);
}

void	mesh_inst_draw(t_r3d *r3d, t_mesh_inst *mesh_inst, t_camera *camera)
{
	r3d_draw_mesh(r3d, mesh_inst->base.scene, mesh_inst->mesh, camera,
		mesh_inst->base.transform);
}
