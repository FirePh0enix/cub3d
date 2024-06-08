/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:17:32 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/08 16:44:19 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"
#include "../math/mat4_init.h"
#include "../math/vec.h"
#include <stdio.h>

static void	draw_vert_line(t_r3d *r3d, int x, int min_y, int max_y, t_color col)
{
	int	y;

	y = min_y;
	while (y <= max_y)
	{
		r3d->color_buffer[x + y * r3d->width] = col;
		y++;
	}
}

void	r3d_raycast_world(t_r3d *r3d, t_map *map)
{
	int	x;

	x = 0;
	while (x < r3d->width)
	{
		double	camera_x = 2 * x / (double)r3d->width - 1;
		double	ray_dir_x = r3d->camera->dir_x + r3d->camera->plane_x * camera_x;
		double	ray_dir_y = r3d->camera->dir_y + r3d->camera->plane_y * camera_x;

		//which box of the map we're in
		int mapX = (int)r3d->camera->position.x;
		int mapY = (int)r3d->camera->position.z;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / ray_dir_x);
		double deltaDistY = fabs(1 / ray_dir_y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (ray_dir_x < 0)
		{
			stepX = -1;
			sideDistX = (r3d->camera->position.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - r3d->camera->position.x) * deltaDistX;
		}
		if (ray_dir_y < 0)
		{
			stepY = -1;
			sideDistY = (r3d->camera->position.z - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - r3d->camera->position.z) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (mapX < 0 || mapX >= map->width || mapY < 0 || mapY >= map->height)
				break ;
			if (map->tiles[mapX + mapY * map->width] == TILE_FULL) hit = 1;
		}

		if (hit)
		{
			if(side == 0) perpWallDist = (sideDistX - deltaDistX);
			else          perpWallDist = (sideDistY - deltaDistY);


			//Calculate height of line to draw on screen
			int lineHeight = (int)(r3d->height / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + r3d->height / 2;
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + r3d->height / 2;
			if(drawEnd >= r3d->height) drawEnd = r3d->height - 1;

			if (side == 1)
				draw_vert_line(r3d, x, drawStart, drawEnd, hex(0x00FF00FF));
			else
				draw_vert_line(r3d, x, drawStart, drawEnd, hex(0x00FF0000));
		}

		x++;
	}
}
