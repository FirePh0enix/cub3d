/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:32:35 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/08 16:31:20 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"

static void	draw_gui_base(t_r3d *r3d, t_gui_base *base);

static t_v2i	screen_coords(t_r3d *r3d, t_v2 v)
{
	t_v2i	ov;

	ov.x = (1 + v.x) * 0.5 * r3d->width;
	ov.y = (1 + v.y) * 0.5 * r3d->height;
	return (ov);
}

static void	draw_panel(t_r3d *r3d, t_panel *panel)
{
	t_v2i	pos;
	t_v2i	size;
	int		x;
	int		y;
	size_t	i;

	pos = screen_coords(r3d, panel->base.pos);
	size = screen_coords(r3d, panel->size);
	x = pos.x - 1;
	if (panel->bg_color.t != 0xFF)
	{
		while (++x < size.x)
		{
			y = pos.y - 1;
			while (++y < size.y)
			{
				r3d->fb->color[x + y * r3d->width] = panel->bg_color;
			}
		}
	}
	i = 0;
	while (i < ft_vector_size(panel->children))
	{
		draw_gui_base(r3d, panel->children[i]);
		i++;
	}
}

static void	draw_gui_base(t_r3d *r3d, t_gui_base *base)
{
	if (base->type == GUI_PANEL)
		draw_panel(r3d, (t_panel *) base);
}

void	r3d_draw_gui(t_r3d *r3d, t_panel *panel)
{
	draw_panel(r3d, panel);
}
