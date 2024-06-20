/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:23:51 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/23 15:29:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_vector_size(void *vec)
{
	if (!vec)
		return (0);
	return (((t_vecdata *)(vec - sizeof(t_vecdata)))->size);
}

void	ft_vector_free(void *vec)
{
	if (!vec)
		return ;
	free(vec - sizeof(t_vecdata));
}

t_vecdata	*ft_vector_data(void *vec)
{
	return (vec - sizeof(t_vecdata));
}

void	ft_vector_iter(void *vec, void (*f)(void*))
{
	const unsigned int	size = ft_vector_size(vec);
	unsigned int		i;

	i = 0;
	while (i < size)
	{
		f(vec + i * ft_vector_data(vec)->el_size);
		i++;
	}
}

char	**ft_vector_from_array(char *array[], size_t count)
{
	char	**vec;
	size_t	i;

	vec = ft_vector(sizeof(char *), count);
	if (!vec)
		return (NULL);
	i = 0;
	while (i < count)
		ft_vector_add(&vec, &array[i++]);
	return (vec);
}
