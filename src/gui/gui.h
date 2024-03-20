/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:45:22 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/20 21:22:05 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "../math/vec.h"
# include "../render/types.h"
# include "libft.h"
# include <stdbool.h>

typedef enum e_gui_type
{
	GUI_PANEL,
	GUI_LABEL
}	t_gui_type;

typedef struct s_gui_base t_gui_base;

typedef void (*t_gui_free)(t_gui_base *);

/*
 * The base structure of any GUI element, those elements should start with this
 * structure.
 */
typedef struct s_gui_base
{
	t_gui_type	type;
	t_v2		pos;
	t_gui_free	free_fn;
}	t_gui_base;

typedef struct s_panel
{
	t_gui_base	base;
	t_gui_base	**children;
	t_v2		size;

	t_color		bg_color;
}	t_panel;

t_panel	*gui_panel_new(t_v2 pos);
void	gui_panel_free(t_panel *panel);

typedef struct s_label
{
	t_gui_base	base;
	char		*name;
}	t_label;

t_label	*gui_label_new(t_v2 pos);
void	gui_label_free(t_label *label);

#endif
