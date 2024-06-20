/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:34:05 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/27 13:19:51 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n - i >= 8)
	{
		*((uint64_t *)(dest + i)) = *((uint64_t *)(src + i));
		i += 8;
	}
	while (i < n)
	{
		*((uint8_t *)(dest + i)) = *((uint8_t *)(src + i));
		i++;
	}
	return (dest);
}
