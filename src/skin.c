/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:00:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 12:13:36 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "render/render.h"

static char	*fmt(char *buf, char *format, char *name)
{
	ft_sprintf(buf, format, name);
	return (buf);
}

static void load_shoot_anim(t_sprite *sh, char *name, t_alloc_table *at)
{
	char	buf[128];

	sh[FORW] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/1.tga", name),
		fmt(buf, "assets/%s/F/1.tga", name),
		fmt(buf, "assets/%s/G/1.tga", name)
	), 3, false, 100);
	sh[FORW_L] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/2.tga", name),
		fmt(buf, "assets/%s/F/2.tga", name),
		fmt(buf, "assets/%s/G/2.tga", name)
	), 3, false, 100);
	sh[LEFT] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/3.tga", name),
		fmt(buf, "assets/%s/F/3.tga", name),
		fmt(buf, "assets/%s/G/3.tga", name)
	), 3, false, 100);
	sh[BACK_L] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/4.tga", name),
		fmt(buf, "assets/%s/F/4.tga", name),
		fmt(buf, "assets/%s/G/4.tga", name)
	), 3, false, 100);
	sh[BACK] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/5.tga", name),
		fmt(buf, "assets/%s/F/5.tga", name),
		fmt(buf, "assets/%s/G/5.tga", name)
	), 3, false, 100);
	sh[BACK_R] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/6.tga", name),
		fmt(buf, "assets/%s/F/6.tga", name),
		fmt(buf, "assets/%s/G/6.tga", name)
	), 3, false, 100);
	sh[RIGHT] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/7.tga", name),
		fmt(buf, "assets/%s/F/7.tga", name),
		fmt(buf, "assets/%s/G/7.tga", name)
	), 3, false, 100);
	sh[FORW_R] = sprite_create_anim(load_images(at, 3,
		fmt(buf, "assets/%s/E/8.tga", name),
		fmt(buf, "assets/%s/F/8.tga", name),
		fmt(buf, "assets/%s/G/8.tga", name)
	), 3, false, 100);
}

static void	load_main_anim(t_sprite *sp, char *name, t_alloc_table *at)
{
	char	buf[128];

	sp[FORW] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/1.tga", name)
	), 1, true, 40);
	sp[FORW_L] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/2.tga", name)
	), 1, true, 40);
	sp[LEFT] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/3.tga", name)
	), 1, true, 40);
	sp[BACK_L] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/4.tga", name)
	), 1, true, 40);

	sp[BACK] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/5.tga", name)
	), 1, true, 40);
	sp[BACK_R] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/6.tga", name)
	), 1, true, 40);
	sp[RIGHT] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/7.tga", name)
	), 1, true, 40);
	sp[FORW_R] = sprite_create_anim(load_images(at, 1,
		fmt(buf, "assets/%s/A/8.tga", name)
	), 1, true, 40);
}

void	load_skin(t_sprite *sp, t_sprite *sh, t_sprite *death, char *name, t_alloc_table *at)
{
	load_shoot_anim(sh, name, at);
	load_main_anim(sp, name, at);
}
