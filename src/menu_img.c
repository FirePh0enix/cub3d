/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:52:46 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/13 11:54:42 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "render/render.h"

void	img_draw(t_menu_img *img, t_r3d *r3d)
{
	sprite_draw_single(r3d, img->image, img->pos, img->scale);
}
