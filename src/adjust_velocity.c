#include "cub3d.h"
#include "libft.h"
#include "math/v3.h"
#include "render/render.h"
#include "scene.h"
#include <X11/Xlib.h>
#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static void	collide_x(t_player *player, t_map *map, float delta, t_entity **ent)
{
	const float	precision = 0.01;

	while (player->base.velocity.x < -0.02 || player->base.velocity.x > 0.02)
	{
		if (!collide_map(box_from_velocity_x(&player->base, delta), map)
			&& !collide_entities(ent, box_from_velocity_x(&player->base, delta)))
			break ;
		if (player->base.velocity.x > 0)
			player->base.velocity.x -= precision;
		else
			player->base.velocity.x += precision;
	}
	if (player->base.velocity.x >= -EPSILON
		&& player->base.velocity.x <= EPSILON)
		player->base.velocity.x = 0;
}

static void	collide_y(t_player *player, t_map *map, float delta, t_entity **ent)
{
	const float	precision = 0.01;

	while (player->base.velocity.y < -0.02 || player->base.velocity.y > 0.02)
	{
		if (!collide_map(box_from_velocity_y(&player->base, delta), map)
			&& !collide_entities(ent, box_from_velocity_y(&player->base, delta)))
			break ;
		if (player->base.velocity.y > 0)
			player->base.velocity.y -= precision;
		else
			player->base.velocity.y += precision;
	}
	if (player->base.velocity.y >= -EPSILON
		&& player->base.velocity.y <= EPSILON)
		player->base.velocity.y = 0;
}

static void	collide_z(t_player *player, t_map *map, float delta, t_entity **ent)
{
	const float	precision = 0.01;

	while (player->base.velocity.z < -0.02 || player->base.velocity.z > 0.02)
	{
		if (!collide_map(box_from_velocity_z(&player->base, delta), map)
			&& !collide_entities(ent, box_from_velocity_z(&player->base, delta)))
			break ;
		if (player->base.velocity.z > 0)
			player->base.velocity.z -= precision;
		else
			player->base.velocity.z += precision;
	}
	if (player->base.velocity.z >= -EPSILON
		&& player->base.velocity.z <= EPSILON)
		player->base.velocity.z = 0.0;
}

void	adjust_vel(t_player *player, t_map *map, float delta, t_entity **ent)
{
	collide_x(player, map, delta, ent);
	collide_y(player, map, delta, ent);
	collide_z(player, map, delta, ent);
}
