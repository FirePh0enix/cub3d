/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:39:09 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 00:02:46 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "types.h"
#include <stdio.h>

void	read_pixels_nomap_32(t_image *image, char *buf, size_t len)
{
	int			i;
	uint32_t	*pixels;
	t_color		col;

	if (len < image->w * image->h * sizeof(uint32_t) + sizeof(t_tga_hdr))
		return ;
	pixels = (uint32_t *) buf;
	i = 0;
	while (i < image->w * image->h)
	{
		col = *(t_color *)&pixels[i];
		col.t = 255 - col.t;
		image->data[i] = col;
		i++;
	}
}

void	read_pixels_nomap_24(t_image *image, char *buf, size_t len)
{
	int		i;
	t_rgb	*pixels24;

	if (len < image->w * image->h * sizeof(t_rgb) + sizeof(t_tga_hdr))
		return ;
	pixels24 = (t_rgb *) buf;
	i = 0;
	while (i < image->w * image->h)
	{
		image->data[i] = hex(*(uint32_t *)pixels24[i] & 0xFFFFFF00 >> 8);
		i++;
	}
}

void	read_pixels_map_32(t_image *image, t_tga_hdr *hdr, char *buf,
	size_t len)
{
	int			i;
	uint8_t		*pixels8;
	uint32_t	*pixels;
	t_color		c;

	if (len < sizeof(t_tga_hdr) + image->w * image->h * sizeof(uint8_t)
		+ (hdr->cmapent >> 3) * hdr->cmaplen)
		return ;
	pixels = (uint32_t *) buf;
	pixels8 = (uint8_t *)(buf + (hdr->cmapent >> 3) * hdr->cmaplen);
	i = 0;
	while (i < image->w * image->h)
	{
		c = ((t_color *)pixels)[pixels8[i]];
		c.t = 255 - c.t;
		image->data[i] = c;
		i++;
	}
}

void	read_pixels_map_24(t_image *image, t_tga_hdr *hdr, char *buf,
	size_t len)
{
	int		i;
	uint8_t	*pixels8;
	t_rgb	*pixels24;
	t_color	c;

	if (len < sizeof(t_tga_hdr) + image->w * image->h * sizeof(uint8_t)
		+ (hdr->cmapent >> 3) * hdr->cmaplen)
		return ;
	pixels24 = (t_rgb *) buf;
	pixels8 = (uint8_t *)(buf + (hdr->cmapent >> 3) * hdr->cmaplen);
	i = 0;
	while (i < image->w * image->h)
	{
		c = (t_color)(*(uint32_t *)pixels24[pixels8[i]] & 0xFFFFFF00 >> 8);
		c.t = 255 - c.t;
		image->data[i] = c;
		i++;
	}
}

void	read_pixels_gray_8(t_image *image, char *buf, size_t len)
{
	uint8_t	*pixels8;
	int		i;
	t_color	c;

	if (len < sizeof(t_tga_hdr) + image->w * image->h * sizeof(uint8_t))
		return ;
	pixels8 = (uint8_t *)buf;
	i = 0;
	while (i < image->w * image->h)
	{
		c = rgba(pixels8[i], pixels8[i], pixels8[i], 0);
		c.t = 255 - c.t;
		image->data[i] = c;
		i++;
	}
}
