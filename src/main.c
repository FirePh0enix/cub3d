/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 00:24:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/render.h"
#include "mlx.h"
#include "benchmark.h"

#include <math.h>

static void	close_hook(void *p)
{
	mlx_loop_end(p);
}

int	main(int argc, char *argv[])
{
	t_v3	vertices[] = {
		{-1.0, -1.0, -5.0}, {1.0, -1.0, -5.0}, {0.0, 1.0, -5.0},
		{-1.0 + 2.5, -1.0, -5.0}, {1.0 + 2.5, -1.0, -5.0}, {0.0 + 2.5, 1.0, -5.0},
		{-1.0 - 2.5, -1.0, -5.0}, {1.0 - 2.5, -1.0, -5.0}, {0.0 - 2.5, 1.0, -5.0},
	};
	t_r3d	r3d;
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 1280, 720, "cub3d");
	t_mesh	*mesh = mesh_load_from_data(vertices, 9);

	mlx_hook(win, DestroyNotify, 0, (void *) close_hook, mlx);
	r3d_init(&r3d, mlx, 1280, 720);
	BENCH(r3d_draw_scene, r3d_draw_scene(&r3d, mesh));
	mlx_put_image_to_window(mlx, win, r3d.buffer, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}
