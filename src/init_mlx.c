/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:18:43 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 16:34:50 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	close_hook(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
}

static void	print_health(t_vars *vars)
{
	const int	percent = ((float)vars->map.player->health / (float)MAX_HEALTH) * 100.0;
	char	buf[32];

	ft_sprintf(buf, "%d %%", percent);
	font_draw_str(&vars->r3d, &vars->bffont, buf, posnscale((t_v2i){
		.x = 0,
		.y = 500
	}, 3));
}

static void limit_frame(t_vars *vars)
{
	suseconds_t	delta;

	delta = getms() - vars->last_update;
	if (delta < 16)
		return ;
	vars->last_update = getms();
	vars->delta_sec = delta / 1000.0;
	if (vars->delta_sec < LIMIT_LOW)
		vars->delta_sec = LIMIT_LOW;
	else if (vars->delta_sec > LIMIT_HIGH)
		vars->delta_sec = LIMIT_HIGH;
}

static void	loop_hook(t_vars *vars)
{
	limit_frame(vars);
	r3d_clear_color_buffer(&vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(&vars->r3d);
	if (vars->menu_open)
		menu_tick(&vars->menu, vars);
	map_tick(vars, &vars->map);
	if (vars->is_server)
		netserv_poll(&vars->server, vars);
	else if (vars->client.has_send_connect)
	{
		netclient_poll(&vars->client, vars);
		netclient_pulse(&vars->client);
	}
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

bool init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_putstr_fd(RED"Error\nMLX pointed returned NULL\n"RESET, 2);
		ft_free(vars, &vars->at);
		return (false);
	}
	vars->win = mlx_new_window(vars->mlx, 1280, 720, "cub3D");
	if (!vars->win)
	{
		ft_putstr_fd(RED"Error\nFailed to create the windows\n"RESET, 2);
		ft_free(vars, &vars->at);
		return (false);
	}
	mlx_hook(vars->win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_pressed_hook, &vars);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, key_released_hook, &vars);
	mlx_hook(vars->win, ButtonPress, ButtonPressMask, (void *)mouse_button_pressed_hook, &vars);
	mlx_hook(vars->win, ButtonRelease, ButtonReleaseMask, (void *)mouse_button_released_hook, &vars);

	mlx_loop_hook(vars->mlx, (void *) loop_hook, &vars);
	return (true);
}
