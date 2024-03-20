/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:19:08 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/20 14:52:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>

static char	*read_to_string(char *filename)
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
		str = realloc(str, /*str_size + 1,*/ str_size + n + 1);
		if (!str)
			return (close(fd), NULL);
		ft_memcpy(str + str_size, buffer, n);
		str[str_size + n] = '\0';
		str_size += n;
	}
	return (close(fd), str);
}

static void	read_header(int *width, int *height, char **s)
{
	int	max_colors;

	*s += 3;
	*width = ft_atoi(*s);
	while (**s >= '0' && **s <= '9')
		*s += 1;
	*s += 1;
	*height = ft_atoi(*s);
	while (**s >= '0' && **s <= '9')
		*s += 1;
	*s += 1;
	max_colors = ft_atoi(*s);
	while (**s >= '0' && **s <= '9')
		*s += 1;
	*s += 1;
	(void) max_colors;
}

static void	read_pixels(t_ppm *ppm, char *buf)
{
	int	i;
	int	j;

	ppm->data = malloc(sizeof(unsigned int) * ppm->width * ppm->height);
	i = 0;
	j = 0;
	while (i < ppm->width * ppm->height * 3)
	{
		uint8_t	r, g, b;
		r = buf[i++];
		g = buf[i++];
		b = buf[i++];
		((unsigned int *) ppm->data)[j++] = (r << 16) | (g << 8) | (b << 0) | (0xFF << 24);
	}
}

t_ppm	*ppm_load_from_file(char *filename)
{
	t_ppm	*ppm;
	char	*s, *s2;

	s = s2 = read_to_string(filename);
	if (!s)
		return (NULL);
	ppm = malloc(sizeof(t_ppm));
	read_header(&ppm->width, &ppm->height, &s);
	printf("%d %d\n", ppm->width, ppm->height);
	read_pixels(ppm, s);
	free(s2);
	return (ppm);
}
