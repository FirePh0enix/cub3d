#include "../scene.h"
#include "../cub3d.h"
#include "mlx.h"
#include "../math/utils.h"
#include <stdio.h>
#include "../math/matrix.h"

void	fake_player_tick(t_vars *vars, t_fake_player *fake_player)
{
	(void) vars;
	(void) fake_player;
	if (fake_player->health <= 0 && vars->is_server)
	{
		// printf("PACKET SENT\n");
		fake_player->base.is_dead = true;
		netserv_broadcast_dead_player(&vars->server, fake_player->base.id, -1);
	}
}

void	fake_player_draw(t_r3d *r3d, t_fake_player *fake_player, t_vars *vars)
{
}

t_fake_player	*fake_player_new(t_vars *vars, t_scene *scene, int id)
{
	t_fake_player	*fake_player;

	(void) vars;
	fake_player = ft_calloc(1, sizeof(t_player));
	fake_player->base.type = ENTITY_FAKE_PLAYER;
	fake_player->base.id = id;
	fake_player->base.tick = (void *) fake_player_tick;
	fake_player->base.draw = (void *) fake_player_draw;
	fake_player->base.transform = (t_transform){};
	fake_player->base.scene = scene;
	fake_player->base.velocity = v3(0, 0, 0);
	fake_player->base.height = 1.0;
	fake_player->base.width = 0.7;
	fake_player->base.depth = 0.7;
	fake_player->health = 1;

	fake_player->sp[FORW] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA1.tga"
	), 1, true, 40);
	fake_player->sp[FORW_L] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA2.tga"
	), 1, true, 40);
	fake_player->sp[LEFT] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA3.tga"
	), 1, true, 40);
	fake_player->sp[BACK_L] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA4.tga"
	), 1, true, 40);

	fake_player->sp[BACK] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA5.tga"
	), 1, true, 40);
	fake_player->sp[BACK_R] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA6.tga"
	), 1, true, 40);
	fake_player->sp[RIGHT] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA7.tga"
	), 1, true, 40);
	fake_player->sp[FORW_R] = sprite_create_anim(load_images(1,
		"assets/player/A/PLAYA8.tga"
	), 1, true, 40);

	return (fake_player);
}

t_image	*fake_player_get_image(t_fake_player *fp, t_vars *vars)
{
	const t_v3	dir_cam =  mat4_multiply_v3(mat4_rotation(vars->r3d->camera->rotation), v3(0, 0, -1));
	const t_v3	dir_fp = mat4_multiply_v3(mat4_rotation(fp->base.transform.rotation), v3(0, 0, 1));
	const float dot = v3_dot(dir_cam, dir_fp);

	// FIXME:
	// Need also to check `dir_cam.y < dir_fp.y` if the camera is looking toward the X axis

	if (dot < -0.75)
		return sprite_get_image(&fp->sp[BACK]);
	else if (dot < -0.25 && dir_cam.x < dir_fp.x)
		return sprite_get_image(&fp->sp[BACK_R]);
	else if (dot < -0.25 && dir_cam.x > dir_fp.x)
		return sprite_get_image(&fp->sp[BACK_L]);
	else if (dot < 0.25 && dir_cam.x < dir_fp.x)
		return sprite_get_image(&fp->sp[RIGHT]);
	else if (dot < 0.25 && dir_cam.x > dir_fp.x)
		return sprite_get_image(&fp->sp[LEFT]);
	else if (dot < 0.75 && dir_cam.x < dir_fp.x)
		return sprite_get_image(&fp->sp[FORW_R]);
	else if (dot < 0.75 && dir_cam.x > dir_fp.x)
		return sprite_get_image(&fp->sp[FORW_L]);
	else
		return sprite_get_image(&fp->sp[FORW]);
}
