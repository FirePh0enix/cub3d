/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:52:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 14:49:06 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "../math/v2i.h"
# include "../mem.h"

typedef struct s_image	t_image;
typedef struct s_vars	t_vars;
typedef struct s_r3d	t_r3d;

typedef struct s_font
{
	t_image	**images;
}	t_font;

t_font	*font_create(t_alloc_table *at);
t_image	*font_get_image(t_font *font, char c);

void	font_draw_str(t_r3d *r3d, t_font *font, char *str, t_v2i pos, float scale);

#endif
