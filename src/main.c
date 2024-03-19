/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/19 23:12:19 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render/render.h"
#include "mlx.h"
#include "benchmark.h"

#include <math.h>
#include <sys/select.h>
#include <sys/time.h>

static t_mesh *teapot;

static void	close_hook(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
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

	vars->r3d->rot_z -= 0.03;
	opts.wireframe_color = hex(0xFF00FFFF);
	opts.solid_color = hex(0xFFFFFFFF);
	r3d_clear_color_buffer(vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(vars->r3d);
	//r3d_draw_mesh(vars->r3d, teapot, &opts);
	BENCH_FUNC(draw, r3d_draw_mesh(vars->r3d, teapot, &opts));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d->canvas, 0, 0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	r3d_key_hook(keycode, vars->r3d);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	vars.r3d = malloc(sizeof(t_r3d));
	vars.last_update = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D");
	teapot = mesh_load_from_obj(&vars, "models/TestCube.obj");
	mlx_hook(vars.win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_loop_hook(vars.mlx, (void *) loop_hook, &vars);
	r3d_init(vars.r3d, vars.mlx, 1280, 720);
	vars.r3d->rot_z = M_PI / 3; // M_PI / 3;

	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
