/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:52:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/21 18:13:08 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

typedef struct s_ppm	t_ppm;

/*
 * The font use PPM file which does not support transparency, so `bg` stores
 * the background color that need to be removed when displaying the character.
 */
typedef struct s_font
{
	t_ppm			*ppm;
	int				x_size;
	int				y_size;
	unsigned int	bg;
}	t_font;

t_font	*font_load_from_file(char *filename, int x_size);
void	font_destroy(t_font *font);
int		font_x_offset(t_font *font, char c);

#endif
