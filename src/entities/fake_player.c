#include "../scene.h"
#include "../cub3d.h"
#include <stdio.h>

void	fake_player_tick(t_vars *vars, t_fake_player *fp)
{
	t_sprite	*sp;

	(void) vars;
	if (fp->health <= 0 && vars->is_server)
	{
		// printf("PACKET SENT\n");
		fp->base.is_dead = true;
		netserv_broadcast_dead_player(&vars->server, fp->base.id, -1);
	}

	if (fp->is_shooting)
	{
		sp = fake_player_get_sprite(fp, vars);
		sprite_tick(sp);
		if (sprite_is_end(sp))
			fp->is_shooting = false;
	}
}

void	fake_player_draw(t_r3d *r3d, t_fake_player *fake_player, t_vars *vars)
{
	(void) r3d;
	(void) fake_player;
	(void) vars;
}

t_fake_player	*fake_player_new(t_vars *vars, t_map *map, int id, t_alloc_table *at)
{
	t_fake_player	*fake_player;

	(void) vars;
	fake_player = ft_calloc(1, sizeof(t_fake_player));
	fake_player->base.type = ENTITY_FAKE_PLAYER;
	fake_player->base.id = id;
	fake_player->base.tick = (void *) fake_player_tick;
	fake_player->base.draw = (void *) fake_player_draw;
	fake_player->base.transform = (t_transform){0};
	fake_player->base.map = map;
	fake_player->base.velocity = v3(0, 0, 0);
	fake_player->base.height = 1.0;
	fake_player->base.width = 0.7;
	fake_player->base.depth = 0.7;
	fake_player->health = MAX_HEALTH;

	fake_player->sp[FORW] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA1.tga"
	), 1, true, 40);
	fake_player->sp[FORW_L] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA2.tga"
	), 1, true, 40);
	fake_player->sp[LEFT] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA3.tga"
	), 1, true, 40);
	fake_player->sp[BACK_L] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA4.tga"
	), 1, true, 40);

	fake_player->sp[BACK] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA5.tga"
	), 1, true, 40);
	fake_player->sp[BACK_R] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA6.tga"
	), 1, true, 40);
	fake_player->sp[RIGHT] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA7.tga"
	), 1, true, 40);
	fake_player->sp[FORW_R] = sprite_create_anim(load_images(at, 1,
		"assets/player/A/PLAYA8.tga"
	), 1, true, 40);

	fake_player->sh[FORW] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE1.tga",
		"assets/player/F/PLAYF1.tga",
		"assets/player/G/PLAYG1.tga"
	), 3, false, 100);
	fake_player->sh[FORW_L] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE2.tga",
		"assets/player/F/PLAYF2.tga",
		"assets/player/G/PLAYG2.tga"
	), 3, false, 100);
	fake_player->sh[LEFT] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE3.tga",
		"assets/player/F/PLAYF3.tga",
		"assets/player/G/PLAYG3.tga"
	), 3, false, 100);
	fake_player->sh[BACK_L] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE4.tga",
		"assets/player/F/PLAYF4.tga",
		"assets/player/G/PLAYG4.tga"
	), 3, false, 100);
	fake_player->sh[BACK] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE5.tga",
		"assets/player/F/PLAYF5.tga",
		"assets/player/G/PLAYG5.tga"
	), 3, false, 100);
	fake_player->sh[BACK_R] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE6.tga",
		"assets/player/F/PLAYF6.tga",
		"assets/player/G/PLAYG6.tga"
	), 3, false, 100);
	fake_player->sh[RIGHT] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE7.tga",
		"assets/player/F/PLAYF7.tga",
		"assets/player/G/PLAYG7.tga"
	), 3, false, 100);
	fake_player->sh[FORW_R] = sprite_create_anim(load_images(at, 3,
		"assets/player/E/PLAYE8.tga",
		"assets/player/F/PLAYF8.tga",
		"assets/player/G/PLAYG8.tga"
	), 3, false, 100);

	return (fake_player);
}

t_image	*fake_player_get_image(t_fake_player *fp, t_vars *vars)
{
	return (sprite_get_image(fake_player_get_sprite(fp, vars)));
}

t_sprite		*fake_player_get_sprite(t_fake_player *fp, t_vars *vars)
{
	const t_v3	dir_cam =  mat4_multiply_v3(mat4_rotation(vars->r3d.camera->rotation), v3(0, 0, -1));
	const t_v3	dir_fp = mat4_multiply_v3(mat4_rotation(fp->base.transform.rotation), v3(0, 0, 1));
	const float dot = v3_dot(dir_cam, dir_fp);

	t_sprite	*sp;

	if (!fp->is_shooting)
		sp = fp->sp;
	else
		sp = fp->sh;

	// FIXME:
	// Need also to check `dir_cam.y < dir_fp.y` if the camera is looking toward the X axis

	if (dot < -0.75)
		return &sp[BACK];
	else if (dot < -0.25 && dir_cam.x < dir_fp.x)
		return &sp[BACK_R];
	else if (dot < -0.25 && dir_cam.x > dir_fp.x)
		return &sp[BACK_L];
	else if (dot < 0.25 && dir_cam.x < dir_fp.x)
		return &sp[RIGHT];
	else if (dot < 0.25 && dir_cam.x > dir_fp.x)
		return &sp[LEFT];
	else if (dot < 0.75 && dir_cam.x < dir_fp.x)
		return &sp[FORW_R];
	else if (dot < 0.75 && dir_cam.x > dir_fp.x)
		return &sp[FORW_L];
	else
		return &sp[FORW];
}

void	fp_reset_shoot_anim(t_fake_player *fp)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		fp->sh[i].current_frame = 0;
		fp->sh[i].last_frame_tick = getms();
		i++;
	}
}
