/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:07:55 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/26 23:38:56 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "../cub3d.h"
#include "types.h"

static void	_raycast_entity2(t_r3d *r3d, t_image *im, t_re_param p)
{
	t_v2i	draw_start;
	t_v2i	draw_end;
	t_v2i	i;
	t_v2i	t;

	draw_start.y = maxi2(-p.sx.y / 2 + r3d->h / 2, 0);
	draw_end.y = mini2(p.sx.y / 2 + r3d->h / 2, r3d->h - 1);
	draw_start.x = maxi2(-p.sx.x / 2 + p.ssx, 0);
	draw_end.x = mini2(p.sx.x / 2 + p.ssx, r3d->w - 1);
	i.x = draw_start.x - 1;
	while (++i.x < draw_end.x)
	{
		t.x = (256 * (i.x - (-p.sx.x / 2 + p.ssx))
				* im->w / p.sx.x) / 256;
		if (!(p.t.y > 0 && i.x > 0 && i.x < r3d->w && p.t.y < r3d->depth[i.x]))
			continue ;
		i.y = draw_start.y - 1;
		while (++i.y < draw_end.y)
		{
			t.y = (((i.y * 256 - r3d->h * 128 + p.sx.y * 128)
						* im->h) / p.sx.y) / 256;
			if (im->data[t.x + im->w * t.y].t == 0)
				r3d->color[i.x + i.y * r3d->w] = im->data[t.x + im->w * t.y];
		}
	}
}

static void	_raycast_entity(t_r3d *r3d, t_entity *entity, t_image *image)
{
	t_v2	sp;
	t_v2	transform;
	int		sprite_screen_x;
	t_v2i	sprite_size;

	sp.x = entity->transform.position.x - r3d->camera->pos.x;
	sp.y = entity->transform.position.z - r3d->camera->pos.z;
	transform.x = (r3d->camera->dir_y * sp.x - r3d->camera->dir_x * sp.y)
		/ (r3d->camera->plane_x * r3d->camera->dir_y - r3d->camera->dir_x
			* r3d->camera->plane_y);
	transform.y = (-r3d->camera->plane_y * sp.x + r3d->camera->plane_x * sp.y)
		/ (r3d->camera->plane_x * r3d->camera->dir_y - r3d->camera->dir_x
			* r3d->camera->plane_y);
	sprite_screen_x = (int)((r3d->w / 2.0) * (1 + transform.x / transform.y));
	sprite_size.x = abs2(r3d->h / transform.y);
	sprite_size.y = abs2(r3d->h / transform.y);
	_raycast_entity2(r3d, image, (t_re_param){transform, sprite_screen_x,
		sprite_size});
}

static float	dist(t_v3 a, t_v3 b)
{
	return (v3_length_squared(v3_sub(a, b)));
}

static void	sort_entities_by_distance(t_entity **entities, t_v3 pos)
{
	t_entity	*swap;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < ft_vector_size(entities))
	{
		j = i;
		while (j > 0 && dist(entities[j - 1]->transform.position, pos)
			< dist(entities[j]->transform.position, pos))
		{
			swap = entities[j];
			entities[j] = entities[j - 1];
			entities[j - 1] = swap;
			j--;
		}
		i++;
	}
}

void	raycast_entities(t_r3d *r3d, t_vars *vars)
{
	t_entity	*entity;
	t_image		*image;
	int			i;

	sort_entities_by_distance(vars->map.entities,
		vars->map.player->base.transform.position);
	i = -1;
	while (++i < (int)ft_vector_size(vars->map.entities))
	{
		entity = vars->map.entities[i];
		if (entity->type != ENTITY_FAKE_PLAYER || entity->is_dead)
			continue ;
		image = fake_player_get_image((void *)entity, vars);
		_raycast_entity(r3d, entity, image);
	}
}
