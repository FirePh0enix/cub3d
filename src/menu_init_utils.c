/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:46:07 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 14:46:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"

void	init_dead(t_menu *menu, t_alloc_table *at, t_i_param p)
{
	t_image	*img;

	img = tga_load_from_file("assets/M_DEAD.tga", at);
	if (!img)
		return ;
	menu->dead_msg = (t_button){.scale = p.s, .image = img,
		.box = {.min = {p.w / 2 - img->w * p.s / 2,
		p.h / 2 - img->h * p.s / 2 - 140
	}, .max = {p.w / 2 - img->w * p.s / 2 + img->w * p.s,
		p.h / 2 - img->h * p.s / 2 + img->h * p.s - 140
	}},
		.pressed = NULL
	};
	img = tga_load_from_file("assets/M_RESPAWN.tga", at);
	if (!img)
		return ;
	menu->respawn = (t_button){.scale = p.s, .image = img,
		.box = {.min = {p.w / 2 - img->w * p.s / 2,
		p.h / 2 - img->h * p.s / 2
	}, .max = {p.w / 2 - img->w * p.s / 2 + img->w * p.s,
		p.h / 2 - img->h * p.s / 2 + img->h * p.s
	}},
		.pressed = (void *) respawn_pressed
	};
}
