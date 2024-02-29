/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/01 00:24:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/render.h"
#include "mlx.h"

static void	close_hook(void *p)
{
	mlx_loop_end(p);
}

int	main(int argc, char *argv[])
{
	const t_triangle	triangle = {{-1.0, -1.0, -5.0}, {1.0, -1.0, -5.0},
		{0.0, 1.0, -5.0}};
	t_r3d	r3d;
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 1280, 720, "cub3d");

	mlx_hook(win, DestroyNotify, 0, (void *) close_hook, mlx);
	r3d_init(&r3d, mlx, 1280, 720);
	r3d_raycast_triangle(&r3d, triangle);
	mlx_put_image_to_window(mlx, win, r3d.buffer, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}
