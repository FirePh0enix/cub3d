/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:42:29 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/12 11:46:30 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "../cub3d.h"
#include <stdint.h>
#include <stdio.h>
#include "../mem.h"

static char	*__read_to_string(char *filename, int *size)
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
			return (close(fd), NULL);
		str = ft_realloc(str, str_size, str_size + n);
		if (!str)
			return (close(fd), NULL);
		ft_memcpy(str + str_size, buffer, n);
		str_size += n;
	}
	*size = str_size;
	return (close(fd), str);
}

char	*read_to_string(char *filename, int *size, t_alloc_table *at)
{
	char	*oldptr;
	char	*ptr;
	int		oldptr_size;

	oldptr = __read_to_string(filename, &oldptr_size);
	if (!oldptr)
		return (NULL);
	ptr = salloc(at, oldptr_size + 1);
	if (!ptr)
		return (free(oldptr), NULL);
	ft_memcpy(ptr, oldptr, oldptr_size);
	free(oldptr);
	ptr[oldptr_size] = '\0';
	if (size)
		*size = oldptr_size;
	return (ptr);
}

static void	read_pixels(t_image *image, t_tga_hdr *hdr, char *buf, size_t len)
{
	if (image->bpp == 32)
		read_pixels_nomap_32(image, buf, len);
	else if (image->bpp == 24)
		read_pixels_nomap_24(image, buf, len);
	else if (image->bpp == 8 && hdr->colormap == 1 && hdr->cmapent == 32)
		read_pixels_map_32(image, hdr, buf, len);
	else if (image->bpp == 8 && hdr->colormap == 1 && hdr->cmapent == 24)
		read_pixels_map_24(image, hdr, buf, len);
	else if (image->bpp == 8 && hdr->colormap == 0)
		read_pixels_gray_8(image, buf, len);
	else
		ft_printf("Invalid Targa format (%d bpp, cmap = %d, cmap_bpp = %d)\n",
			image->bpp, hdr->colormap, hdr->cmapent);
}

t_image	*tga_load_from_file(char *filename, t_alloc_table *at)
{
	char		*s;
	t_tga_hdr	hdr;
	t_image		*image;
	int			size;

	s = read_to_string(filename, &size, at);
	if (!s)
		return (NULL);
	ft_memcpy(&hdr, s, sizeof(t_tga_hdr));
	image = salloc(at, sizeof(t_image));
	if (!image)
		return (sfree(at, (void *)s), NULL);
	image->data = salloc(at, sizeof(uint32_t) * hdr.w * hdr.h);
	if (!image->data)
		return (sfree(at, (void *)s), sfree(at, (void *)image), NULL);
	image->w = hdr.w;
	image->h = hdr.h;
	image->bpp = hdr.bpp;
	read_pixels(image, &hdr, (char *)s + sizeof(t_tga_hdr), size);
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
	image->w = width;
	image->h = height;
	return (image);
}
