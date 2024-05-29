/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/28 16:28:01 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "gui/gui.h"
#include "libft.h"
#include "network/net.h"
#include "render/font.h"
#include "render/render.h"
#include "mlx.h"
#include "scene.h"

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>

static void	close_hook(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
}

suseconds_t	getms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	print_fps(t_vars *vars, suseconds_t delta, suseconds_t frame_time)
{
	float	f;
	char	buf[128];

	f = (1.0 / (delta / 16.0)) * 60.0;
	ft_sprintf(buf, "fps: %d, delta: %d ms", (int) f, (int) frame_time);
	r3d_draw_text(vars->r3d, vars->font, buf, (t_v2){-1.0, -1.0});
}

#define LIMIT_HIGH 0.0167
#define LIMIT_LOW  0.0100

static void	loop_hook(t_vars *vars)
{
	suseconds_t	delta;

	delta = getms() - vars->last_update;
	if (delta < 16)
		return ;
	vars->last_update = getms();
	vars->delta_sec = delta / 1000.0;

	if (vars->delta_sec < LIMIT_LOW)
		vars->delta_sec = LIMIT_LOW;
	else if (vars->delta_sec > LIMIT_HIGH)
		vars->delta_sec = LIMIT_HIGH;

#ifndef _USE_RENDER_THREAD
	// vars->r3d->rot_z -= 0.03;
	r3d_clear_color_buffer(vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(vars->r3d);

	tick_scene(vars, vars->scene);
	draw_scene(vars->r3d, vars->scene, vars->scene->player->camera, vars);

	if (vars->is_server)
		netserv_poll(&vars->server, vars);
	else
		netclient_poll(&vars->client, vars);

	r3d_draw_walls(vars->r3d, vars->map);
	print_fps(vars, delta, getms() - vars->last_update);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d->canvas, 0, 0);
#else
	if (vars->is_server)
		netserv_poll(&vars->server, vars);

	tick_scene(vars, vars->scene);
	// print_fps(vars, delta, getms() - vars->last_update);
#endif
}

#ifdef _USE_RENDER_THREAD

static void	render_thread(t_vars *vars)
{
	while (vars->running)
	{
		mlx_do_sync(vars->mlx);

		r3d_clear_color_buffer(vars->r3d, hex(0x0));
		r3d_clear_depth_buffer(vars->r3d);

		draw_scene(vars->r3d, vars->scene, vars->scene->player->camera, vars);
		r3d_draw_walls(vars->r3d, vars->map);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d->canvas, 0, 0);
	}
}

#endif

int	main(int argc, char *argv[])
{
	t_vars	vars;
	char	**map;
	char	**new_map;

	(void) argc;
	vars.r3d = ft_calloc(sizeof(t_r3d), 1);
	vars.last_update = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D");
	vars.map = ft_calloc(sizeof(t_map), 1);
	map = create_map(argv[1], vars.map);
	new_map = fill_map_with_space(map, vars.map->width, vars.map->height);
	map_to_tiles(vars.map, new_map);
	// is_map_surrounded(new_map, vars.map);
	find_player_pos(new_map, vars.map);
	fill_texture(vars.map, argv[1]);
	mlx_hook(vars.win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_pressed_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released_hook, &vars);
	mlx_hook(vars.win, ButtonPress, ButtonPressMask, (void *)mouse_button_pressed_hook, &vars);
	mlx_hook(vars.win, ButtonRelease, ButtonReleaseMask, (void *)mouse_button_released_hook, &vars);

	mlx_loop_hook(vars.mlx, (void *) loop_hook, &vars);

	r3d_init(vars.r3d, vars.mlx, 1280, 720);

	vars.keys = ft_calloc(0xFFFF, sizeof(bool));

	// vars.panel = gui_panel_new((t_v2){-1.0, -1.0});
	// vars.panel->bg_color = hex(0xFF000000);
	// vars.panel->size = (t_v2){0.0, 0.0};

	vars.font = font_load_from_file("assets/JetBrainsMono.tga");
	vars.south = tga_load_from_file("assets/cobblestone.tga");

	bake_map(vars.map, &vars);

	vars.enemy_mesh = mesh_load_from_obj(&vars, "assets/enemy.obj");

	vars.scene = create_scene();

	t_light	light = {
		.type = LIGHT_DIRECTIONAL,
		.direction = v3(-1.0, 0.0, 0.0),
		.color = hex(0x00FFFFFF),
		.intensity = 1.0,
	};
	ft_vector_add(&vars.scene->lights, &light);

	t_player	*player = player_new(&vars, vars.scene, next_entity_id(&vars));
	player->base.transform.position = v3(3.0, 0.0, -3.0);
	scene_add_entity(vars.scene, player);
	vars.scene->player = player;

	mlx_hook(vars.win, MotionNotify, PointerMotionMask, (void *) player_mouse_event, &vars);

	vars.r3d->camera = vars.scene->player->camera;

	if (argc == 3 && !ft_strcmp(argv[2], "host"))
	{
		vars.is_server = true;
		netserv_init(&vars.server, &vars);
	}
	else if (argc == 5 && !ft_strcmp(argv[2], "connect"))
	{
		vars.is_server = false;
		netclient_init(&vars.client, argv[3], CLIENT_PORT);
		netclient_connect(&vars.client, argv[4]);
	}
	else
	{
		vars.is_server = false;
	}

	mlx_mouse_move(vars.mlx, vars.win, 1280 / 2, 720 / 2);
	// mlx_mouse_hide(vars.mlx, vars.win); // TODO: This may leak memory

#ifdef _USE_RENDER_THREAD
	if (pthread_create(&vars.render_thread, NULL, (void *) render_thread, &vars) != 0)
	{
		ft_printf("Unable to create the render thread.\n");
		return (1);
	}

	vars.running = true;
#endif

	mlx_loop(vars.mlx);

#ifdef _USE_RENDER_THREAD
	vars.running = false;
	pthread_join(vars.render_thread, NULL);
#endif

	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
