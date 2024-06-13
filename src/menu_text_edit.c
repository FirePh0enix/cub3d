/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_text_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:44:33 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/13 12:14:42 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include "render/font.h"
#include <stdio.h>

void	text_edit_draw(t_text_edit *text_edit, t_r3d *r3d, t_vars *vars)
{
	font_draw_str(r3d, vars->font, text_edit->buffer, text_edit->box.min, 6);
}

void	text_edit_tick(t_text_edit *text_edit, t_vars *vars)
{
	(void) text_edit;
	(void) vars;
}

void	text_edit_key(t_text_edit *text_edit, int c)
{
	if (text_edit->disabled || !text_edit->focused)
		return ;
	if ((c == XK_BackSpace || c == XK_Delete) && text_edit->len > 0)
	{
		text_edit->buffer[--text_edit->len] = '\0';
		return ;
	}
	if (text_edit->filter && !text_edit->filter(c))
		return ;
	if (text_edit->len == TEXT_EDIT_SIZE)
		return ;
	if (c < 32 || c >= 126)
		return ;
	text_edit->buffer[text_edit->len++] = c;
	text_edit->buffer[text_edit->len] = '\0';
}
