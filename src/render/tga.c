/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:42:29 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/05 13:33:40 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include <stdint.h>

char	*read_to_string(char *filename)
{
	int		fd;
	char	*str;
	char	buffer[4096];
	int		str_size;
	int		n;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = NULL;
	str_size = 0;
	n = 4096;
	while (n == 4096)
	{
		n = read(fd, buffer, 4096);
		if (n == -1)
			return (NULL);
		// FIXME Realloc is too slow because it use ft_calloc instead of malloc
		//       Maybe ft_realloc should be splitted ft_realloc (w/o calloc) and
		//       ft_recalloc which use ft_calloc
		str = realloc(str, /*str_size + 1,*/ str_size + n + 1);
		if (!str)
			return (close(fd), NULL);
		ft_memcpy(str + str_size, buffer, n);
		str[str_size + n] = '\0';
		str_size += n;
	}
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
	uint16_t	h;
	uint16_t	w;
	uint8_t		bpp;
	uint8_t		pixel_type;
} __attribute__((packed))	t_tga_hdr;

typedef uint8_t	t_rgb[3];

static void	read_pixels(t_image *image, char *buf)
{
	uint32_t	*pixels;
	t_rgb		*pixels24;
	int			i;

	if (image->bpp == 32)
	{
		pixels = (uint32_t *) buf;
		i = 0;
		while (i < image->width * image->height)
		{
			image->data[i] = pixels[i];
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
	else
		ft_printf("Invalid Targa format : %d bits per pixel\n", image->bpp);
}

t_image	*tga_load_from_file(char *filename)
{
	const char	*s = read_to_string(filename);
	t_tga_hdr	hdr;
	t_image		*image;

	if (!s)
		return (NULL);
	ft_memcpy(&hdr, s, sizeof(t_tga_hdr));
	image = malloc(sizeof(t_image));
	if (!image)
		return (free((void *)s), NULL);
	image->data = malloc(sizeof(uint32_t) * hdr.w * hdr.h);
	image->width = hdr.w;
	image->height = hdr.h;
	image->bpp = hdr.bpp;
	read_pixels(image, (char *)s + sizeof(t_tga_hdr));
	return (image);
}

t_image	*tga_create(int width, int height)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->data = malloc(sizeof(uint32_t) * width * height);
	if (!image->data)
		return (free(image), NULL);
	image->width = width;
	image->height = height;
	return (image);
}
