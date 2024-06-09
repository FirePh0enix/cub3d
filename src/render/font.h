/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:52:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 22:43:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "../math/v2i.h"

typedef struct s_image	t_image;
typedef struct s_vars	t_vars;
typedef struct s_r3d	t_r3d;

typedef struct s_font
{
	t_image	**images;
}	t_font;

t_font	*font_create();
t_image	*font_get_image(t_font *font, char c);

void	font_draw_str(t_r3d *r3d, t_font *font, char *str, t_v2i pos);

#endif
