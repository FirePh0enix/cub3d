/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:40:28 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/24 13:46:48 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUN_H
# define GUN_H

# include "math/v2i.h"
# include "render/render.h"
# include "sound/sound.h"

typedef struct s_gun
{
	t_sprite	main_anim;
	t_sprite	shoot_anim;

	t_sound		main_sound;

	bool		reloading;
	bool		has_shoot;

	t_v2i		main_offset;
	t_v2i		offset;
}	t_gun;

void	tick_gun(t_gun *gun);
void	draw_gun(t_gun *gun, t_r3d *r3d);

#endif
