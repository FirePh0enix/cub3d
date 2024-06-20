/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:34:16 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 18:08:39 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void	*ft_realloc(void *p, size_t on, size_t n)
{
	void	*np;

	np = malloc(n);
	if (!np)
		return (NULL);
	if (p)
	{
		ft_memcpy(np, p, on);
		free(p);
	}
	return (np);
}
