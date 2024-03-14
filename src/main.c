/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/14 12:06:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/render.h"
#include "mlx.h"
#include "benchmark.h"

#include <math.h>

static void *mlx;
static void *win;
static t_mesh *cube, *teapot, *dragon;

static void	close_hook(void *p)
{
	mlx_loop_end(p);
}

static void	loop_hook(t_r3d *r3d)
{
	t_opts	opts;

	opts.draw_wireframe = false;
	opts.draw_depthbuffer = true;
	opts.wireframe_color = hex(0xFF00FFFF);
	opts.solid_color = hex(0xFFFFFFFF);
	r3d_clear_color_buffer(r3d, hex(0x0));
	r3d_clear_depth_buffer(r3d);
	BENCH(r3d_draw_mesh, r3d_draw_mesh(r3d, teapot, &opts), 1);
	mlx_put_image_to_window(mlx, win, r3d->img, 0, 0);
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
	int		indices[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
	};
	t_r3d	r3d;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 720, "cub3D");
	
	cube = mesh_load_from_data(vertices, 36, indices, 36);
	teapot = mesh_load_from_file("teapot.obj");
	//dragon = mesh_load_from_file("dragon.obj");

	mlx_hook(win, DestroyNotify, 0, (void *) close_hook, mlx);
	mlx_loop_hook(mlx, (void *) loop_hook, &r3d);
	r3d_init(&r3d, mlx, 1280, 720);
	//r3d.rot_z = M_PI;
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}
