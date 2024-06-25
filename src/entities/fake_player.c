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

t_fake_player	*fake_player_new(t_vars *vars, t_map *map, int id, t_skin skin)
{
	t_fake_player	*fp;

	(void) vars;
	fp = ft_calloc(1, sizeof(t_fake_player));
	fp->base.type = ENTITY_FAKE_PLAYER;
	fp->base.id = id;
	fp->base.tick = (void *) fake_player_tick;
	fp->base.draw = (void *) fake_player_draw;
	fp->base.transform = (t_transform){0};
	fp->base.map = map;
	fp->base.velocity = v3(0, 0, 0);
	fp->base.height = 1.0;
	fp->base.width = 0.7;
	fp->base.depth = 0.7;
	fp->health = MAX_HEALTH;
	fp->skin = skin;

	ft_memcpy(fp->sp, vars->skin[skin], sizeof(t_sprite[8]));
	ft_memcpy(fp->sh, vars->skin_shoot[skin], sizeof(t_sprite[8]));

	return (fp);
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

	t_sprite	*curr_sp = vars->skin[fp->skin];
	t_sprite	*curr_sh = vars->skin_shoot[fp->skin];

	t_sprite	*sp;

	if (!fp->is_shooting)
		sp = curr_sp;
	else
		sp = curr_sh;

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
