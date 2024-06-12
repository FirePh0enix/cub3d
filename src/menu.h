/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:45:22 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/12 11:01:22 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "libft.h"
# include "math/v2i.h"
# include "render/font.h"
# include <stdbool.h>

typedef struct s_vars	t_vars;

typedef struct s_boxi
{
	t_v2i	min;
	t_v2i	max;
}	t_boxi;

typedef void (*t_button_pressed)(t_vars *vars);

typedef struct s_button
{
	char				*label;
	t_image				*image;
	float				scale;

	t_boxi				box;
	bool				disabled;
	t_button_pressed	pressed;
}	t_button;

void	button_draw(t_button *button, t_r3d *r3d);
void	button_tick(t_button *button, t_vars *vars);

typedef struct s_text_edit
{
	char	*buffer;
	size_t	len;

	t_boxi	box;
	bool	disabled;
}	t_text_edit;

typedef enum e_state
{
	STATE_MAIN,
}	t_state;

typedef struct s_menu
{
	t_state		state;

	t_button	singleplayer;
	t_button	multiplayer;

	// Multiplayer
	t_button	host;
	t_button	join;
	t_text_edit	ip;
}	t_menu;

void	menu_draw(t_menu *menu, t_r3d *r3d);
void	menu_tick(t_menu *menu, t_vars *vars);

#endif
