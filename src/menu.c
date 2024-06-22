/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:03:54 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/23 01:00:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include "mem.h"
#include "mlx.h"
#include "network/net.h"
#include "render/render.h"
#include <stdio.h>

static void	save_data(t_menu *menu)
{
	int	fd;

	fd = open("cub3d-ip", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (write(fd, menu->ip.buffer, menu->ip.len) == -1)
		return ;
	close(fd);
	fd = open("cub3d-name", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (write(fd, menu->name.buffer, menu->name.len) == -1)
		return ;
	close(fd);
}

static void	load_data(t_menu *menu, t_alloc_table *at)
{
	char	*s;

	s = read_to_string("cub3d-ip", NULL, at);
	if (s)
	{
		strncpy(menu->ip.buffer, s, 16);
		// FIXME: Could segfault
		menu->ip.buffer[ft_strlen(s)] = '\0'; 
		menu->ip.len = ft_strlen(menu->ip.buffer);
		// free(s);
	}
	s = read_to_string("cub3d-name", NULL, at);
	if (s)
	{
		strncpy(menu->name.buffer, s, 16);
		menu->name.buffer[ft_strlen(s)] = '\0'; 
		menu->name.len = ft_strlen(menu->name.buffer);
		// free(s);
	}
}

static void	singleplayer_pressed(t_vars *vars)
{
	vars->menu_open = false;
	vars->is_server = true;
}

static void	multiplayer_pressed(t_vars *vars)
{
	vars->menu.state = STATE_MULTIPLAYER;
}

static void	host_pressed(t_vars *vars)
{
	save_data(&vars->menu);
	vars->is_server = true;
	netserv_init(&vars->server, vars, SERVER_PORT);
	strncpy(vars->scoreboard.entries[0].username, vars->menu.name.buffer, 16);
	vars->menu_open = false;
}

static void	join_pressed(t_vars *vars)
{
	save_data(&vars->menu);
	vars->is_server = false;
	netclient_init(&vars->client, vars->menu.ip.buffer, SERVER_PORT);
	netclient_connect(&vars->client, vars->menu.name.buffer);
}

static bool	ip_filter(char c)
{
	return (c == '.' || (c >= '0' && c <= '9'));
}

static bool	name_filter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void	menu_init(t_menu *menu, t_r3d *r3d, t_alloc_table *at)
{
	const int	w = r3d->width;
	const int	h = r3d->height;
	const int 	s = 3;

	// Main state
	t_image *img = tga_load_from_file("assets/M_SING.tga", at);
	menu->singleplayer = (t_button){
		.disabled = false,
		.label = NULL,
		.scale = 3.0,
		.image = img,
		.box = { .min = {
			w / 2 - img->width * s / 2,
			h / 2 - img->height * s / 2 - 120
		}, .max = {
			w / 2 - img->width * s / 2 + img->width * s,
			h / 2 - img->height * s / 2 + img->height * s - 120
		} },
		.pressed = (void *) singleplayer_pressed,
	};
	t_image *img2 = tga_load_from_file("assets/textures/M_MULTI.tga", at);
	menu->multiplayer = (t_button){
		.disabled = false,
		.label = NULL,
		.scale = 3.0,
		.image = img2,
		.box = { .min = {
			w / 2 - img2->width * s / 2,
			h / 2 - img2->height * s / 2
		}, .max = {
			w / 2 - img2->width * s / 2 + img2->width * s,
			h / 2 - img2->height * s / 2 + img2->height * s
		} },
		.pressed = (void *) multiplayer_pressed,
	};

	// Multiplayer state
	t_image *img3 = tga_load_from_file("assets/M_HOST.tga", at);
	menu->host = (t_button){
		.disabled = false,
		.label = NULL,
		.scale = 3.0,
		.image = img3,
		.box = { .min = {
			w / 2 - img3->width * s / 2,
			h / 2 - img3->height * s / 2 - 120
		}, .max = {
			w / 2 - img3->width * s / 2 + img3->width * s,
			h / 2 - img3->height * s / 2 + img3->height * s - 120
		} },
		.pressed = (void *) host_pressed,
	};
	t_image *img4 = tga_load_from_file("assets/M_JOIN.tga", at);
	menu->join = (t_button){
		.disabled = false,
		.label = NULL,
		.scale = 3.0,
		.image = img4,
		.box = { .min = {
			w / 2 - img4->width * s / 2,
			h / 2 - img4->height * s / 2
		}, .max = {
			w / 2 - img4->width * s / 2 + img4->width * s,
			h / 2 - img4->height * s / 2 + img4->height * s
		} },
		.pressed = (void *) join_pressed,
	};
	t_image	*img5 = tga_load_from_file("assets/M_IP.tga", at);
	menu->ip_img = (t_menu_img){
		.scale = 3.0,
		.image = img5,
		.pos = {
			w / 2 - img5->width * s / 2 - 80,
			h / 2 - img5->height * s / 2 + 150
		}
	};
	menu->ip = (t_text_edit){
		.len = 0,
		.disabled = false,
		.focused = false,
		.filter = (void *) ip_filter,
		.box = {
			.min = {
				w / 2 - img5->width * s / 2 - 10,
				h / 2 + 150 - 8 * 6 / 2
			},
			.max = {
				w / 2 - img5->width * s / 2 - 10 + 7 * 6 * 16,
				h / 2 + 150 - 8 * 6 / 2 + 8 * 6
			}
		},
	};

	t_image	*img6 = tga_load_from_file("assets/M_NAME.tga", at);
	menu->name_img = (t_menu_img){
		.scale = 3.0,
		.image = img6,
		.pos = {
			w / 2 - img6->width * s / 2 - 140,
			h / 2 - img6->height * s / 2 + 210
		}
	};
	menu->name = (t_text_edit){
		.len = 0,
		.disabled = false,
		.focused = false,
		.filter = (void *) name_filter,
		.box = {
			.min = {
				w / 2 - img6->width * s / 2 + 30,
				h / 2 + 210 - 8 * 6 / 2
			},
			.max = {
				w / 2 - img6->width * s / 2 + 30 + 7 * 6 * 16,
				h / 2 + 210 - 8 * 6 / 2 + 8 * 6
			}
		},
	};

	load_data(menu, at);
}

bool	mouse_click_over(t_vars *vars, t_boxi box)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	return (x >= box.min.x && x <= box.max.x && y >= box.min.y && y <= box.max.y && vars->buttons[1]);
}

void	menu_draw(t_menu *menu, t_r3d *r3d, t_vars *vars)
{
	if (menu->state == STATE_MAIN)
	{
		button_draw(&menu->singleplayer, r3d);
		button_draw(&menu->multiplayer, r3d);
	}
	else if (menu->state == STATE_MULTIPLAYER)
	{
		button_draw(&menu->host, r3d);
		button_draw(&menu->join, r3d);

		img_draw(&menu->ip_img, r3d);
		text_edit_draw(&menu->ip, r3d, vars);

		img_draw(&menu->name_img, r3d);
		text_edit_draw(&menu->name, r3d, vars);
	}
}

void	menu_tick(t_menu *menu, t_vars *vars)
{
	if (menu->state == STATE_MAIN)
	{
		button_tick(&menu->singleplayer, vars);
		button_tick(&menu->multiplayer, vars);
	}
	else if (menu->state == STATE_MULTIPLAYER)
	{
		button_tick(&menu->host, vars);
		button_tick(&menu->join, vars);

		text_edit_tick(&menu->ip, vars);
		text_edit_tick(&menu->name, vars);

		if (mouse_click_over(vars, menu->ip.box))
		{
			menu->ip.focused = true;
			menu->name.focused = false;
		}
		else if (mouse_click_over(vars, menu->name.box))
		{
			menu->ip.focused = false;
			menu->name.focused = true;
		}
	}
	if (!vars->buttons[1])
		menu->already_pressed = false;
}

void	menu_key(t_menu *menu, t_vars *vars, int c)
{
	(void) vars;
	if (menu->state == STATE_MULTIPLAYER)
	{
		text_edit_key(&menu->ip, c);
		text_edit_key(&menu->name, c);
	}
}
