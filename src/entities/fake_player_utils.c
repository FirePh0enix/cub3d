/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:32:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/11 23:58:17 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scene.h"
#include "../cub3d.h"
#include <math.h>

static t_sprite	*sprite_for_angle(t_v3 dir_cam, t_v3 dir_fp, t_sprite *sp)
{
	const float	dot = dir_cam.x * dir_fp.x + dir_cam.z * dir_fp.z;
	const float	det = dir_cam.x * dir_fp.z - dir_cam.z * dir_fp.x;
	const float	angle = atan2(dot, det) * 180.0 / M_PI;

	if (angle <= -157.0 || angle >= 157.0)
		return (&(sp[FORW]));
	else if (angle < -112.5)
		return (&sp[FORW_R]);
	else if (angle > 112.0)
		return (&sp[FORW_L]);
	else if (angle < -67.5)
		return (&sp[RIGHT]);
	else if (angle > 67.5)
		return (&sp[LEFT]);
	else if (angle < -22.5)
		return (&sp[BACK_R]);
	else if (angle > 22.5)
		return (&sp[BACK_L]);
	return (&sp[BACK]);
}

t_sprite	*fake_player_get_sprite(t_fake_player *fp, t_vars *vars)
{
	const t_v3		dir_cam = mat4_multiply_v3(
			mat4_rotation(vars->r3d.camera->rot), v3(0, 0, -1));
	const t_v3		dir_fp = mat4_multiply_v3(
			mat4_rotation(fp->base.transform.rotation), v3(1, 0, 0));
	const t_sprite	*curr_sp = vars->skin[fp->skin];
	const t_sprite	*curr_sh = vars->skin_shoot[fp->skin];
	t_sprite		*sp;

	if (!fp->is_shooting)
		sp = (void *) curr_sp;
	else
		sp = (void *) curr_sh;
	return (sprite_for_angle(dir_cam, dir_fp, sp));
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
