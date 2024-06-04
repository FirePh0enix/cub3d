/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/04 16:10:29 by ledelbec         ###   ########.fr       */
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
#include <string.h>
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

static void	print_scoreboard(t_vars *vars)
{
	const float		step = 0.1;
	int				i;
	float			y;
	char			buf[128];

	i = 0;
	y = -1.0;
	while (i < MAX_CLIENT + 1)
	{
		if (vars->scoreboard.entries[i].present)
		{
			ft_sprintf(buf, "%s | %d | %d", vars->scoreboard.entries[i].username, vars->scoreboard.entries[i].kills, vars->scoreboard.entries[i].death);
			r3d_draw_text(vars->r3d, vars->font, buf, (t_v2){r3d_get_text_size(vars->r3d, vars->font, buf) / 2.0, y});
		}
		y += step;
		i++;
	}
}

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
	{
		netserv_poll(&vars->server, vars);
		netserv_broadcast_scoreboard(&vars->server, &vars->scoreboard);
	}
	else
	{
		netclient_poll(&vars->client, vars);
		netclient_pulse(&vars->client);
	}

	r3d_draw_walls(vars->r3d, vars->map);
	print_fps(vars, delta, getms() - vars->last_update);

	if (vars->keys[XK_Tab])
		print_scoreboard(vars);

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
	char	*line;
	char	**map_file;
	char	**map;
	char	**map_rectangular;
	char	**colors;

	(void) argc;
	ft_bzero(&vars, sizeof(t_vars));
	vars.r3d = ft_calloc(sizeof(t_r3d), 1);
	vars.last_update = 0;
	vars.mlx = mlx_init();
	if (argc == 3 && (!ft_strcmp(argv[2], "host") || !ft_strcmp(argv[2], "local-host")))
		vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D - HOST");
	else if (argc == 5 && (!ft_strcmp(argv[2], "connect") || !ft_strcmp(argv[2], "connect-local")))
		vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D - CLIENT");
	else
		vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D");
	vars.map = ft_calloc(sizeof(t_map), 1);
	line = read_to_string(argv[1]);
	map_file = ft_split(line, '\n');
	map = create_map(map_file, vars.map);
	map_rectangular = fill_map_with_space(map, vars.map->width, vars.map->height);
	map_to_tiles(vars.map, map_rectangular);
	// if (!is_map_surrounded(map_rectangular, vars.map))
		// return 1;
	find_player_pos(map_rectangular, vars.map);
	if (!fill_texture(vars.map, map_file))
		return 1;
	colors = create_colors(map_file);
	if (!is_valid_rgb(colors, vars.map))
		return 1;
	mlx_hook(vars.win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_pressed_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released_hook, &vars);
	mlx_hook(vars.win, ButtonPress, ButtonPressMask, (void *)mouse_button_pressed_hook, &vars);
	mlx_hook(vars.win, ButtonRelease, ButtonReleaseMask, (void *)mouse_button_released_hook, &vars);

	mlx_loop_hook(vars.mlx, (void *) loop_hook, &vars);

	r3d_init(vars.r3d, vars.mlx, 1280, 720);

	vars.keys = ft_calloc(0xFFFF, sizeof(bool));
	vars.scoreboard.entries[0].present = 1;

	// vars.panel = gui_panel_new((t_v2){-1.0, -1.0});
	// vars.panel->bg_color = hex(0xFF000000);
	// vars.panel->size = (t_v2){0.0, 0.0};

	vars.font = font_load_from_file("assets/JetBrainsMono.tga");

	bake_map(vars.map, &vars);

	vars.enemy_mesh = mesh_load_from_obj(&vars, "assets/enemy.obj");
	vars.half_door = mesh_load_from_obj(&vars, "assets/Door.obj");

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

	t_door	*door = door_new(&vars, vars.scene, 0, next_entity_id(&vars));
	door->base.transform.position.z = -4.0;
	door->base.transform.position.y = 1.5;
	scene_add_entity(vars.scene, door);

	mlx_hook(vars.win, MotionNotify, PointerMotionMask, (void *) player_mouse_event, &vars);

	vars.r3d->camera = vars.scene->player->camera;

	if (argc == 4 && !ft_strcmp(argv[2], "host"))
	{
		vars.is_server = true;
		netserv_init(&vars.server, &vars, SERVER_PORT);
		strncpy(vars.scoreboard.entries[0].username, argv[3], 16);
	}
	else if (argc == 4 && !ft_strcmp(argv[2], "local-host"))
	{
		vars.is_server = true;
		netserv_init(&vars.server, &vars, SERVER_LOCAL_PORT);
		strncpy(vars.scoreboard.entries[0].username, argv[3], 16);
	}
	else if (argc == 5 && !ft_strcmp(argv[2], "connect"))
	{
		vars.is_server = false;
		netclient_init(&vars.client, argv[3], SERVER_PORT);
		netclient_connect(&vars.client, argv[4]);
	}
	else if (argc == 5 && !ft_strcmp(argv[2], "connect-local"))
	{
		vars.is_server = false;
		netclient_init(&vars.client, argv[3], SERVER_LOCAL_PORT);
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

	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop(vars.mlx);
	mlx_do_key_autorepeaton(vars.mlx);

#ifdef _USE_RENDER_THREAD
	vars.running = false;
	pthread_join(vars.render_thread, NULL);
#endif

	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
