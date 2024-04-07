/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/07 13:40:38 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "gui/gui.h"
#include "render/font.h"
#include "render/render.h"
#include "mlx.h"
#include "benchmark.h"

#include <math.h>
#include <sys/select.h>
#include <sys/time.h>

static t_mesh	*teapot;
static t_image	*img;
static t_wall	wall1;
static t_light	*lights;

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

static void	print_fps(t_vars *vars, suseconds_t delta, suseconds_t frame_time)
{
	float	f;
	char	buf[128];

	f = delta / 16.0 * 60.0;
	ft_sprintf(buf, "fps: %d, delta: %d ms", (int) f, (int) frame_time);
	r3d_draw_text(vars->r3d, vars->font, buf, (t_v2){-1.0, -1.0});
}

static void	loop_hook(t_vars *vars)
{
	suseconds_t	delta;

	delta = getms() - vars->last_update;
	if (delta < 16)
		return ;
	vars->last_update = getms();

	vars->r3d->rot_z -= 0.03;
	r3d_clear_color_buffer(vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(vars->r3d);
	BENCH_FUNC(mesh, r3d_draw_mesh(vars->r3d, teapot, lights));
	BENCH_FUNC(wall, r3d_draw_wall(vars->r3d, &wall1, lights));

	//r3d_draw_gui(vars->r3d, vars->panel);
	//r3d_draw_text(vars->r3d, vars->font, "Hello world!", (t_v2){-1.0, -1.0});
	
	print_fps(vars, delta, getms() - vars->last_update);
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
	teapot = mesh_load_from_obj(&vars, "models/knight.obj");
	mlx_hook(vars.win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_loop_hook(vars.mlx, (void *) loop_hook, &vars);
	r3d_init(vars.r3d, vars.mlx, 1280, 720);
	vars.r3d->rot_z = M_PI / 3;

	vars.panel = gui_panel_new((t_v2){-1.0, -1.0});
	vars.panel->bg_color = hex(0xFF000000);
	vars.panel->size = (t_v2){0.0, 0.0};

	vars.font = font_load_from_file("assets/JetBrainsMono.tga");
	img = tga_load_from_file("models/gold_ore.tga");

	wall1 = wall(v3(0, 0, -4), 0, img);

	lights = ft_vector(sizeof(t_light), 0);
	t_light	light = {
		.type = LIGHT_POINT,
		.position = v3(-10, 0, -4),
		.intensity = 1.0,
		.color = hex(0x000000FF),
	};
	ft_vector_add(&lights, &light);
	t_light	light2 = {
		.type = LIGHT_POINT,
		.position = v3(10, 0, -3.5),
		.intensity = 1.0,
		.color = hex(0x0000FF00),
	};
	ft_vector_add(&lights, &light2);

	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
