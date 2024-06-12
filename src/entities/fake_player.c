#include "../scene.h"
#include "../cub3d.h"
#include "mlx.h"
#include "../math/utils.h"
#include <stdio.h>
#include "../math/mat4_init.h"

void	fake_player_tick(t_vars *vars, t_fake_player *fake_player)
{
	(void) vars;
	(void) fake_player;
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

	return (fake_player);
}
