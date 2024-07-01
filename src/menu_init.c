/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:30:39 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 14:46:28 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"

static void	init_main(t_menu *menu, t_alloc_table *at, t_i_param p)
{
	t_image	*img;

	img = tga_load_from_file("assets/M_SING.tga", at);
	if (!img)
		return ;
	menu->singleplayer = (t_button){.scale = p.s, .image = img,
		.box = {.min = {p.w / 2 - img->w * p.s / 2,
		p.h / 2 - img->h * p.s / 2 - 120}, .max = {
		p.w / 2 - img->w * p.s / 2 + img->w * p.s,
		p.h / 2 - img->h * p.s / 2 + img->h * p.s - 120}},
		.pressed = (void *) singleplayer_pressed,
	};
	img = tga_load_from_file("assets/textures/M_MULTI.tga", at);
	if (!img)
		return ;
	menu->multiplayer = (t_button){.scale = p.s, .image = img,
		.box = {.min = {p.w / 2 - img->w * p.s / 2, p.h / 2 - img->h * p.s / 2
	}, .max = {p.w / 2 - img->w * p.s / 2 + img->w * p.s,
		p.h / 2 - img->h * p.s / 2 + img->h * p.s}},
		.pressed = (void *) multiplayer_pressed,
	};
}

static void	init_multi1(t_menu *menu, t_alloc_table *at, t_i_param p)
{
	t_image	*img;

	img = tga_load_from_file("assets/M_HOST.tga", at);
	if (!img)
		return ;
	menu->host = (t_button){.scale = p.s, .image = img,
		.box = {.min = {p.w / 2 - img->w * p.s / 2,
		p.h / 2 - img->h * p.s / 2 - 120
	}, .max = {p.w / 2 - img->w * p.s / 2 + img->w * p.s,
		p.h / 2 - img->h * p.s / 2 + img->h * p.s - 120}},
		.pressed = (void *) host_pressed,
	};
	img = tga_load_from_file("assets/M_JOIN.tga", at);
	if (!img)
		return ;
	menu->join = (t_button){.scale = p.s, .image = img,
		.box = {.min = {p.w / 2 - img->w * p.s / 2,
		p.h / 2 - img->h * p.s / 2}, .max = {
		p.w / 2 - img->w * p.s / 2 + img->w * p.s,
		p.h / 2 - img->h * p.s / 2 + img->h * p.s}},
		.pressed = (void *) join_pressed,
	};
}

static void	init_multi2(t_menu *menu, t_alloc_table *at, t_i_param p)
{
	t_image	*img;

	img = tga_load_from_file("assets/M_IP.tga", at);
	if (!img)
		return ;
	menu->ip_img = (t_menu_img){.scale = p.s, .image = img,
		.pos = {p.w / 2 - img->w * p.s / 2 - 80,
		p.h / 2 - img->h * p.s / 2 + 150}
	};
	menu->ip = (t_text_edit){.len = 0, .disabled = false, .focused = false,
		.filter = (void *) ip_filter, .box = {.min = {
		p.w / 2 - img->w * p.s / 2 - 10, p.h / 2 + 150 - 8 * 6 / 2},
		.max = {p.w / 2 - img->w * p.s / 2 - 10 + 7 * 6 * 16,
		p.h / 2 + 150 - 8 * 6 / 2 + 8 * 6}
	}};
}

static void	init_multi3(t_menu *menu, t_alloc_table *at, t_i_param p)
{
	t_image	*img;

	img = tga_load_from_file("assets/M_NAME.tga", at);
	if (!img)
		return ;
	menu->name_img = (t_menu_img){.scale = p.s, .image = img,
		.pos = {p.w / 2 - img->w * p.s / 2 - 140,
		p.h / 2 - img->h * p.s / 2 + 210}
	};
	menu->name = (t_text_edit){.len = 0, .disabled = false, .focused = false,
		.filter = (void *) name_filter, .box = {.min = {
		p.w / 2 - img->w * p.s / 2 + 30,
		p.h / 2 + 210 - 8 * 6 / 2},
		.max = {p.w / 2 - img->w * p.s / 2 + 30 + 7 * 6 * 16,
		p.h / 2 + 210 - 8 * 6 / 2 + 8 * 6
	}}};
}

void	menu_init(t_menu *menu, t_r3d *r3d, t_alloc_table *at)
{
	const t_i_param	p = {r3d->w, r3d->h, 3};

	init_main(menu, at, p);
	init_multi1(menu, at, p);
	init_multi2(menu, at, p);
	init_multi3(menu, at, p);
	load_data(menu, at);
	init_dead(menu, at, p);
}
