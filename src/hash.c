/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:44:46 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/12 12:22:38 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

uint32_t	fnv32_hash(const char *str, size_t len)
{
	const unsigned char	*s = (unsigned char *)str;
	const uint32_t		fnv_32_prime = 0x01000193;
	uint32_t			h;

	h = 0x811c9dc5;
	while (len--)
	{
		h ^= *s++;
		h *= fnv_32_prime;
	}
	return (h);
}

uint32_t	fnv32_hash_file(char *file)
{
	const uint32_t		fnv_32_prime = 0x01000193;
	uint32_t			h;
	int					n;
	int					fd;
	unsigned char		buf[4096];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	h = 0x811c9dc5;
	n = 4096;
	while (n == 4096)
	{
		n = read(fd, buf, 4096);
		if (n == -1)
			return (0);
		while (n--)
		{
			h ^= buf[4096 - n - 1];
			h *= fnv_32_prime;
		}
	}
	close(fd);
	return (h);
}
