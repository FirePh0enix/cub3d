/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:17:32 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/17 16:15:43 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "render.h"
#include "../cub3d.h"
#include "../math/utils.h"
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

static void	raycast_floor_and_ceiling(t_r3d *r3d, t_map *map)
{
	int	x;
	int	y;

	const t_image	*ci = map->ceilling_image;
	const t_image	*fi = map->floor_image;

	y = 0;
	while (y < r3d->height)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = r3d->camera->dir_x - r3d->camera->plane_x;
		float rayDirY0 = r3d->camera->dir_y - r3d->camera->plane_y;
		float rayDirX1 = r3d->camera->dir_x + r3d->camera->plane_x;
		float rayDirY1 = r3d->camera->dir_y + r3d->camera->plane_y;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - r3d->height / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * r3d->height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / r3d->width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / r3d->width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = r3d->camera->position.x + rowDistance * rayDirX0;
		float floorY = r3d->camera->position.z + rowDistance * rayDirY0;

		x = 0;
		while (x < r3d->width)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cell_x = (int)(floorX);
			int cell_y = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx_f = 0;
			int ty_f = 0;

			if (fi)
			{
				tx_f = (int)(fi->width * (floorX - cell_x)) & (fi->width - 1);
				ty_f = (int)(fi->height * (floorY - cell_y)) & (fi->height - 1);
			}

			int tx_c = 0;
			int ty_c = 0;

			if (ci)
			{
				tx_c = (int)(ci->width * (floorX - cell_x)) & (ci->width - 1);
				ty_c = (int)(ci->height * (floorY - cell_y)) & (ci->height - 1);
			}

			floorX += floorStepX;
			floorY += floorStepY;

			if (!fi)
				r3d->color_buffer[x + y * r3d->width]                     = map->floor_color;
			else
				r3d->color_buffer[x + y * r3d->width]                     = hex(fi->data[tx_f + ty_f * fi->width]);
			if (!ci)
				r3d->color_buffer[x + (r3d->height - y - 1) * r3d->width] = map->ceiling_color;
			else
				r3d->color_buffer[x + (r3d->height - y - 1) * r3d->width] = hex(ci->data[tx_c + ty_c * ci->width]);
			x++;
 		}
		y++;
	}
}

static t_image	*texture_for_wall(t_map *map, int side, int ray_dir_x, int ray_dir_y)
{
	if (side == 1)
		return (map->ea);
	else if (side == 0)
		return (map->no);
	// else if (side == 1 && ray_dir_y < 0)
	// 	return (map->so);
	// else if (side == 0 && ray_dir_x >= 0)
	// 	return (map->we);
	// else if (side == 0 && ray_dir_x < 0)
	// 	return (map->ea);
	return (map->no);
}

void	r3d_raycast_world(t_r3d *r3d, t_map *map, t_vars *vars)
{
	int	x;

	raycast_floor_and_ceiling(r3d, map);

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

			int lineHeight = (int)(r3d->height / perpWallDist);

			int drawStart = -lineHeight / 2 + r3d->height / 2;
			if (drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + r3d->height / 2;
			if (drawEnd >= r3d->height) drawEnd = r3d->height - 1;

			if (r3d->mode == MODE_DEPTH)
			{
				if (side == 1)
					draw_vert_line(r3d, x, drawStart, drawEnd, hex(0x00FF00FF));
				else
					draw_vert_line(r3d, x, drawStart, drawEnd, hex(0x00FF0000));
			}
			else
			{
				t_image	*texture;
				if (map->tiles[mapX + mapY * map->width] == TILE_DOOR)
					texture = vars->door;
				else
					texture = texture_for_wall(map, side, ray_dir_x, ray_dir_y);
				double	wall_x;

				if (side == 0) wall_x = r3d->camera->position.z + perpWallDist * ray_dir_y;
				else           wall_x = r3d->camera->position.x + perpWallDist * ray_dir_x;
				wall_x -= floor(wall_x);

				int tex_x = wall_x * texture->width;
				if (side == 0 && ray_dir_x > 0)       tex_x = texture->width - tex_x - 1;
				else if (side == 1 && ray_dir_y < 0)  tex_x = texture->width - tex_x - 1;

				double step = 1.0 * texture->height / lineHeight;
				double texPos = (drawStart - r3d->height / 2.0 + lineHeight / 2.0) * step;
				for(int y = drawStart; y < drawEnd; y++)
				{
					int tex_y = (int)texPos; // & (texture->height - 1);
					texPos += step;
					if (((t_color *)texture->data)[tex_x + tex_y * texture->width].t == 0)
						r3d->color_buffer[x + y * r3d->width] = ((t_color *)texture->data)[tex_x + tex_y * texture->width];
				}
			}

			r3d->depth_buffer[x] = perpWallDist;
		}

		// TODO: Sort 3d sprites for farsest to closest.

		x++;
	}

	for(size_t i = 0; i < ft_vector_size(vars->scene->entities); i++)
	{
		t_entity *entity = vars->scene->entities[i];
		if (entity->type == ENTITY_PLAYER || entity->is_dead)
			continue ;
		t_image	*image = sprite_get_image(&vars->player_sprite);
		const float	x = entity->transform.position.x;
		const float	y = entity->transform.position.z;

		const float	scale = 1.0;

		//translate sprite position to relative to camera
		double spriteX = x - r3d->camera->position.x;
		double spriteY = y - r3d->camera->position.z;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (r3d->camera->plane_x * r3d->camera->dir_y - r3d->camera->dir_x * r3d->camera->plane_y); //required for correct matrix multiplication

		double transformX = invDet * (r3d->camera->dir_y * spriteX - r3d->camera->dir_x * spriteY);
		double transformY = invDet * (-r3d->camera->plane_y * spriteX + r3d->camera->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((r3d->width / 2.0) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs2(r3d->height / transformY) * scale; //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + r3d->height / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + r3d->height / 2;
		if(drawEndY >= r3d->height) drawEndY = r3d->height - 1;

		//calculate width of the sprite
		int spriteWidth = abs2(r3d->height / transformY) * scale;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= r3d->width) drawEndX = r3d->width - 1;
		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * image->width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < r3d->width && transformY < r3d->depth_buffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - r3d->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * image->height) / spriteHeight) / 256;
					t_color color = ((t_color *)image->data)[image->width * texY + texX]; //get current color from the texture
					if (color.t == 0)
						r3d->color_buffer[stripe + y * r3d->width] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}
