/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:00:23 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/12 14:55:46 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "gun.h"
#include "libft.h"
#include "menu.h"
#include "network/net.h"
#include "render/font.h"
#include "render/render.h"
#include "mlx.h"
#include "scene.h"
#include "sound/sound.h"

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
	font_draw_str(vars->r3d, vars->font, buf, (t_v2i){0, 0});
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
			// r3d_draw_text(vars->r3d, vars->font, buf, (t_v2){r3d_get_text_size(vars->r3d, vars->font, buf) / 2.0, y});
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

	r3d_clear_color_buffer(vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(vars->r3d);

	if (!vars->menu_open)
		tick_scene(vars, vars->scene);
	else
		menu_draw(&vars->menu, vars->r3d);
	// draw_scene(vars->r3d, vars->scene, vars->scene->player->camera, vars);

	if (vars->is_server)
	{
		netserv_poll(&vars->server, vars);
		netserv_broadcast_scoreboard(&vars->server, &vars->scoreboard);

		if (vars->scene->player->health <= 0 && vars->is_server)
		{
			vars->scene->player->base.is_dead = true;
			netserv_broadcast_dead_player(&vars->server, vars->scene->player->base.id, -1);
			return ;
		}
	}
	else
	{
		netclient_poll(&vars->client, vars);
		netclient_pulse(&vars->client);
	}

	r3d_raycast_world(vars->r3d, vars->map, vars);

	if (!vars->menu_open)
		draw_gun(&vars->scene->player->gun, vars->r3d);
	else
		menu_tick(&vars->menu, vars);

	// print_fps(vars, delta, getms() - vars->last_update);

	// minimap_draw(&vars->minimap, vars->r3d, (t_v2i){}, (t_v2i){
	// 	vars->r3d->camera->position.x * 20 - 150,
	// 	vars->r3d->camera->position.z * 20 - 150,
	// });

	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d->canvas, 0, 0);
}

static void	singleplayer_pressed(t_vars *vars)
{
	vars->menu_open = false;
}

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
	if (argc == 4 && (!ft_strcmp(argv[2], "host") || !ft_strcmp(argv[2], "local-host")))
		vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D - HOST");
	else if (argc == 5 && (!ft_strcmp(argv[2], "connect") || !ft_strcmp(argv[2], "connect-local")))
		vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D - CLIENT");
	else
		vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D");
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

	vars.shotgun.main_anim = sprite_create_anim(load_images(6,
		"assets/textures/SHTGA0.tga",
		"assets/textures/SHTGB0.tga",
		"assets/textures/SHTGC0.tga",
		"assets/textures/SHTGD0.tga",
		"assets/textures/SHTGC0.tga",
		"assets/textures/SHTGB0.tga"
	), 6, false, 100);
	vars.shotgun.shoot_anim = sprite_create_anim(load_images(2,
		"assets/textures/SHTFA0.tga",
		"assets/textures/SHTFB0.tga"
	), 2, false, 100);
	vars.shotgun.offset = (t_v2i){-18, 96};
	sound_read_from_wav(&vars.shotgun.main_sound, "assets/sound/DSSHOTGN.wav");

	vars.player_sprite = sprite_create(tga_load_from_file("assets/textures/PLAYA1.tga"));

	vars.font = font_create();
	vars.scene = create_scene();

	vars.menu.state = STATE_MAIN;
	vars.menu_open = true;

	t_image *img = tga_load_from_file("assets/M_SING.tga");
	vars.menu.singleplayer = (t_button){
		.disabled = false,
		.label = NULL,
		.scale = 3.0,
		.image = img,
		.box = { .min = {
			vars.r3d->width / 2 - img->width * 3 / 2,
			vars.r3d->height / 2 - img->height * 3 / 2
		}, .max = {
			vars.r3d->width / 2 - img->width * 3 / 2 + img->width * 3,
			vars.r3d->height / 2 - img->height * 3 / 2 + img->height * 3
		} },
		.pressed = (void *) singleplayer_pressed,
	};

	t_player	*player = player_new(&vars, vars.scene, next_entity_id(&vars));
	scene_add_entity(vars.scene, player);
	vars.scene->player = player;

	// t_fake_player *fake_player = fake_player_new(&vars, vars.scene, next_entity_id(&vars));
	// fake_player->base.transform.position.x = 10;
	// fake_player->base.transform.position.z = 10;
	// fake_player->health = 3;
	// scene_add_entity(vars.scene, fake_player);

	mlx_hook(vars.win, MotionNotify, PointerMotionMask, (void *) player_mouse_event, &vars);

	vars.map = ft_calloc(sizeof(t_map), 1);
	line = read_to_string(argv[1], NULL);
	if (!line)
		return 1;
	map_file = ft_split(line, '\n');
	map = create_map(map_file, vars.map);
	map_rectangular = fill_map_with_space(map, vars.map->width, vars.map->height);
	vars.map->maps = map_rectangular;
	map_to_tiles(vars.map, map_rectangular, vars.scene, &vars);
	if (!is_valid_char_in_map(map_rectangular, vars.map))
		return 1;
	if (!is_map_surrounded(map_rectangular, vars.map))
		return 1;
	if (!find_player_pos(map_rectangular, vars.map))
		return 1;
	if (!fill_texture(vars.map, map_file))
		return 1;
	colors = create_colors(map_file);
	if (!colors)
	{
		ft_putstr_fd("Error\nColors malloc failed\n", 2);
		return (1);
	}
	if (!is_valid_rgb(colors, vars.map))
		return 1;
	if (!is_valid_file_name(argv[1]))
		return 1;
	minimap_create(&vars.minimap, vars.map);

	player->base.transform = vars.map->spawns[0];
	player->gun = vars.shotgun;

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
		vars.is_server = true;
	}

	// t_sound	sound;

	// sound_read_from_wav(&sound, "bfg.wav");

	// sound_play(&sound);

	mlx_mouse_move(vars.mlx, vars.win, 1280 / 2, 720 / 2);
	// mlx_mouse_hide(vars.mlx, vars.win); // TODO: This may leak memory

	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop(vars.mlx);
	mlx_do_key_autorepeaton(vars.mlx);

	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
