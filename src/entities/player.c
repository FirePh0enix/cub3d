#include "../scene.h"
#include "../cub3d.h"
#include "mlx.h"
#include "../math/utils.h"
#include <stdio.h>
#include "../math/matrix.h"

void	player_tick(t_vars *vars, t_player *player);
void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera, t_vars *vars);

t_player	*player_new(t_vars *vars, t_scene *scene, int id)
{
	t_player	*player;

	(void) vars;
	player = ft_calloc(1, sizeof(t_player));
	player->base.type = ENTITY_PLAYER;
	player->base.id = id;
	player->base.tick = (void *) player_tick;
	player->base.draw = (void *) player_draw;
	player->base.transform = (t_transform){};
	player->base.scene = scene;
	player->camera = ft_calloc(1, sizeof(t_camera));
	player->base.velocity = v3(0, 0, 0);
	player->base.height = 2.0;
	player->base.width = 0.3;
	player->base.depth = 0.3;

	player->camera->plane_x = 0.0;
	player->camera->plane_x = 0.85;

	player->camera->dir_x = 0;
	player->camera->dir_y = -1;

	player->health = 1;

	return (player);
}

static bool	is_on_ground(t_player *player)
{
	return (player->base.transform.position.y == 0);
}

static void	rotate_y(t_player *player, float rot_speed)
{
	const float	old_plane_x = player->camera->plane_x;
	const float	old_dir_x = player->camera->dir_x;

	player->camera->rotation.y += rot_speed;
	player->base.transform.rotation.y = player->camera->rotation.y;

	player->camera->plane_x = old_plane_x * cos(-rot_speed) - player->camera->plane_y * sin(-rot_speed);
	player->camera->plane_y = old_plane_x * sin(-rot_speed) + player->camera->plane_y * cos(-rot_speed);

	player->camera->dir_x = old_dir_x * cos(-rot_speed) - player->camera->dir_y * sin(-rot_speed);
	player->camera->dir_y = old_dir_x * sin(-rot_speed) + player->camera->dir_y * cos(-rot_speed);
}

void	player_tick(t_vars *vars, t_player *player)
{
	const t_v3	camera_offset = v3(0.0, 1.6, 0.0);
	const t_v3	forward = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0, player->base.transform.rotation.y, 0)), v3(0, 0, -1.0)));
	const t_v3	left = v3_norm(mat4_multiply_v3(mat4_rotation(v3(0, player->base.transform.rotation.y, 0)), v3(-1.0, 0, 0)));
	const float	speed = 5.0;
	const float	jump_force = 20.0;

	if (!vars->is_focused)
		return ;
	if (vars->keys[XK_w])
		player->base.velocity = v3_add(player->base.velocity, v3_scale(forward, speed));
	if (vars->keys[XK_s])
		player->base.velocity = v3_sub(player->base.velocity, v3_scale(forward, speed));
	if (vars->keys[XK_a])
		player->base.velocity = v3_add(player->base.velocity, v3_scale(left, speed));
	if (vars->keys[XK_d])
		player->base.velocity = v3_sub(player->base.velocity, v3_scale(left, speed));

	// TODO: Uncomment when moving up/down is done in raycasting
	// if (vars->keys[XK_space] && !player->has_jump && is_on_ground(player))
	// {
	// 	player->base.velocity.y += jump_force;
	// 	player->has_jump = true;
	// }
	// else if (!vars->keys[XK_space] && is_on_ground(player))
	// 	player->has_jump = false;

	player->base.velocity.y -= 0.8;

	adjust_vel(player, vars->map, vars->delta_sec, vars->scene->entities);

	player->base.transform.position = v3_add(player->base.transform.position, v3_scale(player->base.velocity, vars->delta_sec));

	if (player->base.transform.position.y < 0)
	{
		player->base.transform.position.y = 0;
		player->base.velocity.y = 0;
	}

	player->camera->position = v3_add(player->base.transform.position,
		camera_offset);

	player->base.velocity.x *= 0.5;
	player->base.velocity.z *= 0.5;

	//
	// Camera mouvements with arrows
	//

	// if (vars->keys[XK_Up])
	// {
	// 	player->camera->rotation.x += 0.02;
	// }
	// if (vars->keys[XK_Down])
	// {
	// 	player->camera->rotation.x -= 0.02;
	// }

	float	rot_speed = 0.02;

	if (vars->keys[XK_Left])
		rotate_y(player, rot_speed);
	if (vars->keys[XK_Right])
		rotate_y(player, -rot_speed);

	// player->camera->rotation.x = clampf(player->camera->rotation.x, -M_PI / 2, M_PI / 2);

	//
	// Interactions
	//

	tick_gun(&player->gun);

	if (vars->buttons[1] && !player->gun.has_shoot)
	{
		t_entity *entity = raycast_entity(vars->map, vars->scene, (t_transform){v3(player->camera->position.x, 0, player->camera->position.z),
			player->camera->rotation}, 10.0, ENTITY_FAKE_PLAYER);
		player->gun.has_shoot = true;
		sound_play(&player->gun.main_sound);
		if (entity)
		{
			t_fake_player *fake_player = (t_fake_player *)entity;
			if (!vars->is_server)
				netclient_send_hit(&vars->client, entity, 1);
			else
				fake_player->health -= 1;
		}
	}

	mlx_mouse_move(vars->mlx, vars->win, 1280 / 2.0, 720 / 2.0);

	if (!vars->is_server)
		netclient_send_pos(&vars->client, player->base.transform);
	else
		netserv_broadcast_pos(&vars->server, player, -1);
}

void	player_mouse_event(int x, int y, t_vars *vars)
{
	const float x_speed = x - 1280 / 2.0;
	const float y_speed = y - 720 / 2.0;
	t_player	*player;

	if (!vars->is_focused || vars->menu_open)
		return ;
	player = vars->scene->player;

	// player->camera->rotation.x -= y_speed / 1200.0;
	// player->camera->rotation.x = clampf(player->camera->rotation.x, -M_PI / 2, M_PI / 2);

	rotate_y(player, -x_speed / 2400.0);

	// player->camera->rotation.y -= x_speed / 1200.0;
	// player->base.transform.rotation.y = player->camera->rotation.y;
}

void	player_draw(t_r3d *r3d, t_player *player, t_camera *camera, t_vars *vars)
{
	(void) r3d;
	(void) player;
	(void) camera;
	(void) vars;
}
