/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:44:06 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 11:42:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hash.h"
#include "libft.h"
#include "menu.h"
#include "network/net.h"
#include "render/font.h"
#include "render/render.h"
#include "mlx.h"
#include "scene.h"
#include <netinet/in.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>

#define LIMIT_HIGH 0.0167
#define LIMIT_LOW  0.0100

#if _BONUS == 1

static	void	limit_frame(t_vars *vars, suseconds_t	delta)
{
	vars->last_update = getms();
	vars->delta_sec = delta / 1000.0;
	if (vars->delta_sec < LIMIT_LOW)
		vars->delta_sec = LIMIT_LOW;
	else if (vars->delta_sec > LIMIT_HIGH)
		vars->delta_sec = LIMIT_HIGH;
}

static void	loop_hook(t_vars *vars)
{
	suseconds_t	delta;

	delta = getms() - vars->last_update;
	if (delta < 16)
		return ;
	limit_frame(vars, delta);
	r3d_clear_color_buffer(&vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(&vars->r3d);
	if (vars->menu_open)
		menu_tick(&vars->menu, vars);
	map_tick(vars, &vars->map);
	if (vars->is_server)
		netserv_poll(&vars->server, vars);
	else if (vars->client.has_send_connect)
	{
		netclient_poll(&vars->client, vars);
		netclient_pulse(&vars->client);
	}
	if (!vars->menu_open)
		menu_closed(vars);
	else
		menu_draw(&vars->menu, &vars->r3d, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d.canvas, 0, 0);
}

#else

static void	loop_hook(t_vars *vars)
{
	vars->ticks++;
	if (vars->ticks < 500)
	{
		sqrt(7728382);
		return ;
	}
	vars->ticks = 0;
	vars->delta_sec = 0.001;
	if (vars->delta_sec < LIMIT_LOW)
		vars->delta_sec = LIMIT_LOW;
	else if (vars->delta_sec > LIMIT_HIGH)
		vars->delta_sec = LIMIT_HIGH;
	r3d_clear_color_buffer(&vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(&vars->r3d);
	if (vars->menu_open)
		menu_tick(&vars->menu, vars);
	map_tick(vars, &vars->map);
	if (!vars->menu_open)
		menu_closed(vars);
	else
		menu_draw(&vars->menu, &vars->r3d, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d.canvas, 0, 0);
}

#endif

static int	init_game(t_vars *v, char **av)
{
	init_door(av, v);
	v->tiles[0] = tga_load_from_file("assets/textures/STWALL.tga", &v->at);
	v->tiles[1] = tga_load_from_file("assets/textures/STWALL.tga", &v->at);
	v->tiles[2] = tga_load_from_file("assets/textures/WALL21_3.tga", &v->at);
	v->tiles[3] = tga_load_from_file("assets/textures/WALL21_5.tga", &v->at);
	v->tiles[4] = tga_load_from_file("assets/textures/cave/WOLF6.tga", &v->at);
	v->tiles[5] = tga_load_from_file("assets/textures/cave/WOLF7.tga", &v->at);
	v->tiles[6] = tga_load_from_file("assets/textures/cave/WOLF7B.tga", &v->at);
	v->tiles[7] = tga_load_from_file("assets/textures/cave/WOLF7B.tga", &v->at);
	init_weapons(v);
	if (!font_init(&v->font, &v->at)
		|| !font_init_big(&v->bffont, &v->at)
		|| !load_skin(v->skin[SKIN_MARINE], v->skin_shoot[SKIN_MARINE],
			"player", &v->at))
		return (0);
	menu_init(&v->menu, &v->r3d, &v->at);
	if (!init_player(v))
		return (0);
	mlx_hook(v->win, MotionNotify, PointerMotionMask,
		(void *) player_mouse_event, v);
	minimap_create(&v->minimap, &v->r3d, &v->map);
	v->r3d.camera = &v->map.player->camera;
	mlx_mouse_move(v->mlx, v->win, 1280 / 2, 720 / 2);
	game_loop(v);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_vars			vars;

	(void) argv;
	ft_bzero(&vars, sizeof(t_vars));
	if (!parsing(&vars, argv, &vars.at, argc))
		return (ft_free(&vars, &vars.at), 1);
	vars.exec_hash = fnv32_hash_file("cub3D");
	if (!init_mlx_settings(&vars))
		return (ft_free(&vars, &vars.at), 1);
	mlx_hook(vars.win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_pressed_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released_hook, &vars);
	mlx_hook(vars.win, ButtonPress, ButtonPressMask,
		(void *)mouse_button_pressed_hook, &vars);
	mlx_hook(vars.win, ButtonRelease, ButtonReleaseMask,
		(void *)mouse_button_released_hook, &vars);
	mlx_loop_hook(vars.mlx, (void *) loop_hook, &vars);
	r3d_init(&vars.r3d, vars.mlx, v2i(1280, 720), &vars.at);
	if (!init_game(&vars, argv))
		return (ft_free(&vars, &vars.at), 1);
}
