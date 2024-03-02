/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:05:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 12:30:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../math/vec.h"
# include "types.h"
# include "raycast_mesh.h"
# include <stdbool.h>

t_mesh	*mesh_load_from_data(t_v3 *vertices, size_t vertex_count);
void	mesh_destroy(t_mesh *mesh);

void	r3d_init(t_r3d *r3d, void *mlx, int width, int height);
void	r3d_draw_scene(t_r3d *r3d, t_mesh *mesh);

#endif
