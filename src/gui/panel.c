/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:58:10 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/20 21:17:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"

t_panel	*gui_panel_new(t_v2 pos)
{
	t_panel	*panel;

	panel = ft_calloc(1, sizeof(t_panel));
	panel->base.type = GUI_PANEL;
	panel->base.free_fn = (void *) gui_panel_free;
	panel->base.pos = pos;
	panel->children = ft_vector(sizeof(t_panel), 0);
	return (panel);
}

void	gui_panel_free(t_panel *panel)
{
	ft_vector_free(panel->children);
	free(panel);
}
