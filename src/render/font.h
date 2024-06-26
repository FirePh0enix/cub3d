/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:52:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 18:56:00 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "../math/v2i.h"
# include "../mem.h"
# include <stdbool.h>

typedef struct s_image	t_image;
typedef struct s_vars	t_vars;
typedef struct s_r3d	t_r3d;

typedef struct s_font
{
	t_image	*images[127];
}	t_font;

typedef struct s_posnscale
{
	t_v2i	pos;
	float	scale;
}	t_posnscale;

inline t_posnscale	posnscale(t_v2i pos, float scale)
{
	return ((t_posnscale){pos, scale});
}

bool	font_init(t_font *font, t_alloc_table *at);
bool	font_init_big(t_font *font, t_alloc_table *at);
t_image	*font_get_image(t_font *font, char c);

void	font_draw_str(t_r3d *r3d, t_font *font, char *str, t_posnscale p);

#endif
