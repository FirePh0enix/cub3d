/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:28:17 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/20 12:48:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "../math/vec.h"

/*
 * A Wavefront OBJ file is composed of one or multiple 3D objects.
 *
 * TODO Only the object should store vertex data. The mesh should only store
 *      references to all objects and materials.
 */
typedef struct s_obj
{
	char	*name;
}	t_obj;

/*typedef struct s_mesh
{
	t_mtl	*material;

	t_face	*faces;
	size_t	faces_count;

	t_v3	*vertices;
	size_t	vertices_count;

	t_v2	*textures;
	size_t	textures_count;
}	t_mesh;*/

#endif
