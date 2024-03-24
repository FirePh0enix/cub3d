/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:52:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/24 16:25:30 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

typedef struct s_image	t_image;

typedef struct s_bakedchar
{
	int	x;
	int	y;
	int	width;
	int	height;

	int	xoffset;
	int	yoffset;
	int	xadvance;
	int	page;
	int	chnl;
}	t_bakedchar;

/*
 * The font use PPM file which does not support transparency, so `bg` stores
 * the background color that need to be removed when displaying the character.
 */
typedef struct s_font
{
	t_image			*img;
	t_bakedchar		chars[127];
}	t_font;

t_font	*font_load_from_file(char *filename);
void	font_destroy(t_font *font);

#endif
