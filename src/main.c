/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/15 16:08:11 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render/render.h"
#include "mlx.h"
#include "benchmark.h"

#include <math.h>
#include <sys/select.h>
#include <sys/time.h>

BENCH_GLOBAL_INIT(bench, 16);

static void *mlx;
static void *win;
static t_mesh *cube, *teapot;

static void	close_hook(void *p)
{
	mlx_loop_end(p);
}

suseconds_t	getms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
}

static void	loop_hook(t_vars *vars)
{
	t_opts	opts;

	if (getms() - vars->last_update < 16)
		return ;
	vars->last_update = getms();
	opts.wireframe_color = hex(0xFF00FFFF);
	opts.solid_color = hex(0xFFFFFFFF);
	r3d_clear_color_buffer(vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(vars->r3d);
	r3d_draw_mesh(vars->r3d, teapot, &opts);
	mlx_put_image_to_window(mlx, win, vars->r3d->canvas, 0, 0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	r3d_key_hook(keycode, vars->r3d);
	return (0);
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
	t_vars	vars;

	vars.r3d = malloc(sizeof(t_r3d));
	vars.last_update = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 720, "cub3D");
	cube = mesh_load_from_data(vertices, 36, indices, 36);
	teapot = mesh_load_from_file("testcube.obj");
	mlx_hook(win, DestroyNotify, 0, (void *) close_hook, mlx);
	mlx_hook(win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_loop_hook(mlx, (void *) loop_hook, &vars);
	r3d_init(vars.r3d, mlx, 1280, 720);
	vars.r3d->rot_z = 0;
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}
