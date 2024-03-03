/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/03 13:22:47 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/render.h"
#include "mlx.h"
#include "benchmark.h"

#include <math.h>

static void *mlx;
static void *win;
static t_mesh *mesh;

static void	close_hook(void *p)
{
	mlx_loop_end(p);
}

static void	loop_hook(t_r3d *r3d)
{
	t_opts	opts;

	opts.draw_wireframe = false;
	opts.wireframe_color = hex(0xFF00FFFF);
	r3d_clear_color_buffer(r3d, hex(0x0));
	BENCH(r3d_draw_mesh, r3d_draw_mesh(r3d, mesh, &opts), 1);
	mlx_put_image_to_window(mlx, win, r3d->img, 0, 0);
	r3d->rot_z += 0.0005;
}

int	main(int argc, char *argv[])
{
	t_v3	vertices[] = {
		{ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f },
		
		{ 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f },
		
		{ 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
		
		{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f },
		
		{ 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
	};
	t_r3d	r3d;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 720, "cub3D");
	mesh = mesh_load_from_data(vertices, 36);

	mlx_hook(win, DestroyNotify, 0, (void *) close_hook, mlx);
	mlx_loop_hook(mlx, (void *) loop_hook, &r3d);
	r3d_init(&r3d, mlx, 1280, 720);
	r3d.rot_z = M_PI / 3.5 + 0.32;
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}
