/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:42:29 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 22:55:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "types.h"
#include "../cub3d.h"
#include <stdint.h>
#include <stdio.h>
#include "../mem.h"

size_t	get_file_size(char *filename)
{
	char	b[4096];
	int		n;
	size_t	size;
	int		fd;

	size = 0;
	n = 4096;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	while (n == 4096)
	{
		n = read(fd, b, 4096);
		size += n;
	}
	close(fd);
	return (size);
}

char	*read_to_string(char *filename, size_t *len, t_alloc_table *at)
{
	int		fd;
	char	*str;
	char	buffer[4096];
	int		str_size;
	int		n;
	size_t	file_size;

	file_size = get_file_size(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = malloc(file_size + 1);
	if (!str)
		return (close(fd), NULL);
	str_size = 0;
	n = 4096;
	while (n == 4096)
	{
		n = read(fd, buffer, 4096);
		if (n == -1)
			return (NULL);
		ft_memcpy(str + str_size, buffer, n);
		str[str_size + n] = '\0';
		str_size += n;
	}
	if (len)
		*len = str_size;
	return (close(fd), str);
}

typedef struct s_tga_hdr
{
	uint8_t		magic;
	uint8_t		colormap;
	uint8_t		encoding;
	uint16_t	cmaporig;
	uint16_t	cmaplen;
	uint8_t		cmapent;
	uint16_t	x;
	uint16_t	y;
	uint16_t	w;
	uint16_t	h;
	uint8_t		bpp;
	uint8_t		pixel_type;
} __attribute__((packed))	t_tga_hdr;

typedef uint8_t	t_rgb[3];

static void	read_pixels(t_image *image, t_tga_hdr *hdr, char *buf)
{
	uint32_t	*pixels;
	t_rgb		*pixels24;
	uint8_t		*pixels8;
	int			i;
	t_color		col;

	if (image->bpp == 32)
	{
		pixels = (uint32_t *) buf;
		i = 0;
		while (i < image->width * image->height)
		{
			col = *(t_color *)&pixels[i];
			col.t = 255 - col.t;
			image->data[i] = col.raw;
			i++;
		}
	}
	else if (image->bpp == 24)
	{
		pixels24 = (t_rgb *) buf;
		i = 0;
		while (i < image->width * image->height)
		{
			image->data[i] = (*(uint32_t*)pixels24[i] & 0xFFFFFF00 >> 8);
			i++;
		}
	}
	else if (image->bpp == 8 && hdr->colormap == 1 && hdr->cmapent == 32)
	{
		pixels = (uint32_t *) buf;
		pixels8 = (uint8_t *)(buf + (hdr->cmapent >> 3) * hdr->cmaplen);
		i = 0;
		while (i < image->width * image->height)
		{
			t_color c = ((t_color *)pixels)[pixels8[i]];
			c.t = 255 - c.t;
			image->data[i] = c.raw; // TODO: Check for overflow
			i++;
		}
	}
	else if (image->bpp == 8 && hdr->colormap == 1 && hdr->cmapent == 24)
	{
		pixels24 = (t_rgb *) buf;
		pixels8 = (uint8_t *)(buf + (hdr->cmapent >> 3) * hdr->cmaplen);
		i = 0;
		while (i < image->width * image->height)
		{
			t_color c = (t_color)(*(uint32_t*)pixels24[pixels8[i]] & 0xFFFFFF00 >> 8);
			c.t = 255 - c.t;
			image->data[i] = c.raw; // TODO: Check for overflow
			i++;
		}
	}
	else if (image->bpp == 8 && hdr->colormap == 0)
	{
		pixels8 = (uint8_t *)buf;
		i = 0;
		while (i < image->width * image->height)
		{
			t_color c = rgba(pixels8[i], pixels8[i], pixels8[i], 0);
			c.t = 255 - c.t;
			image->data[i] = c.raw; // TODO: Check for overflow
			i++;
		}
	}
	else
		ft_printf("Invalid Targa format (%d bpp, colormap = %d, colormap bpp = %d)\n", image->bpp, hdr->colormap, hdr->cmapent);
}

t_image	*tga_load_from_file(char *filename, t_alloc_table *at)
{
	const char	*s = read_file(filename, at);
	t_tga_hdr	hdr;
	t_image		*image;

	if (!s)
		return (NULL);
	ft_memcpy(&hdr, s, sizeof(t_tga_hdr));
	image = salloc(at, sizeof(t_image));
	if (!image)
		return (free((void *)s), NULL);
	image->data = salloc(at, sizeof(uint32_t) * hdr.w * hdr.h);
	image->width = hdr.w;
	image->height = hdr.h;
	image->bpp = hdr.bpp;
	read_pixels(image, &hdr, (char *)s + sizeof(t_tga_hdr));
	return (image);
}

t_image	*tga_create(int width, int height, t_alloc_table *at)
{
	t_image	*image;

	image = salloc(at, sizeof(t_image));
	if (!image)
		return (NULL);
	image->data = salloc(at, sizeof(uint32_t) * width * height);
	if (!image->data)
		return (NULL);
	image->width = width;
	image->height = height;
	return (image);
}
