/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:34:16 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 17:05:58 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void	*salloc(t_alloc_table *at, size_t n);

void	*ft_realloc(void *p, size_t on, size_t n, t_alloc_table *at)
{
	void	*np;

	np = salloc(at, n);
	if (!np)
		return (NULL);
	if (p)
	{
		ft_memcpy(np, p, on);
		free(p);
	}
	return (np);
}
