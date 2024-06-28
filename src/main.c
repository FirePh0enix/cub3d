#include "cub3d.h"
#include "gun.h"
#include "hash.h"
#include "libft.h"
#include "menu.h"
#include "network/net.h"
#include "render/font.h"
#include "render/render.h"
#include "mlx.h"
#include "scene.h"

#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>


#if _BONUS == 1

#else

static void	loop_hook(t_vars *vars)
{
	vars->ticks++;
	if (vars->ticks < 500)
	{
		sqrt(7728382);
		return ;
	}
	vars->ticks = 0;
	vars->delta_sec = 0.001;

	if (vars->delta_sec < LIMIT_LOW)
		vars->delta_sec = LIMIT_LOW;
	else if (vars->delta_sec > LIMIT_HIGH)
		vars->delta_sec = LIMIT_HIGH;

	r3d_clear_color_buffer(&vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(&vars->r3d);

	if (vars->menu_open)
		menu_tick(&vars->menu, vars);

	map_tick(vars, &vars->map);

	if (!vars->menu_open)
	{
		r3d_raycast_world(&vars->r3d, &vars->map, vars);
		draw_gun(&vars->map.player->gun[vars->map.player->gun_index], &vars->r3d);
		draw_crosshair(&vars->r3d, vars);
		minimap_draw(&vars->minimap, &vars->r3d, vars);
		print_health(vars);
	}
	else
		menu_draw(&vars->menu, &vars->r3d, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d.canvas, 0, 0);
}

#endif

int	main(int argc, char *argv[])
{
	t_vars			vars;

	ft_bzero(&vars, sizeof(t_vars));
	vars.map.name = argv[1];
	if (!parsing(&vars, argv, &vars.at, argc))
		return (ft_free(&vars, &vars.at));
	if (!init_mlx(&vars))
		return (ft_free(&vars, &vars.at));
	vars.exec_hash = fnv32_hash_file("cub3D");
	vars.last_update = 0;
	r3d_init(&vars.r3d, vars.mlx, v2i(1280, 720), &vars.at);
	vars.door = tga_load_from_file("assets/textures/DOOR2_4.tga", &vars.at);
	vars.crosshair = tga_load_from_file("assets/textures/PL_T.tga", &vars.at);
	if (!font_init(&vars.font, &vars.at) || !font_init_big(&vars.bffont, &vars.at))
		return (ft_free(&vars, &vars.at));
	vars.menu.state = STATE_MAIN;
	vars.menu_open = true;
	load_skin(vars.skin[SKIN_MARINE], vars.skin_shoot[SKIN_MARINE], "player", &vars.at);
	menu_init(&vars.menu, &vars.r3d, &vars.at);
	t_player	*player = player_new(&vars, &vars.map, next_entity_id(&vars));
	map_add_entity(&vars.map, player);
	vars.map.player = player;
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, (void *) player_mouse_event, &vars);
	minimap_create(&vars.minimap, &vars.r3d, &vars.map);
	player->base.transform = vars.map.spawns[0];
	player->spawn_transform = vars.map.spawns[0];
	vars.r3d.camera = vars.map.player->camera;
	mlx_mouse_move(vars.mlx, vars.win, 1280 / 2, 720 / 2);
	// mlx_mouse_hide(vars.mlx, vars.win); // TODO: This may leak memory
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop(vars.mlx);
	mlx_do_key_autorepeaton(vars.mlx);
	ft_free(&vars, &vars.at);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
