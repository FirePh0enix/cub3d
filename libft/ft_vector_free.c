/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:52:46 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/23 15:34:01 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	free_inner(void **v)
{
	free(*v);
}

void	ft_vector_deep_free(void *vec)
{
	if (!vec)
		return ;
	ft_vector_iter(vec, (void *) free_inner);
	ft_vector_free(vec);
}
