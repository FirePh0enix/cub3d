/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:51:47 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/24 16:51:35 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	str(char *s)
{
	const size_t	size = ft_strlen(s);
	t_str			str;

	str.data = ft_strdup(s);
	str.size = size;
	str.capacity = size + 1;
	return (str);
}

void	*str_append(t_str *str, char *s)
{
	const size_t	size = ft_strlen(s);

	if (!str->data)
		return (NULL);
	if (str->size + size + 1 > str->capacity)
	{
		str->data = ft_realloc(str->data, str->capacity, str->capacity + size);
		if (!str->data)
			return (NULL);
		str->capacity += size;
	}
	ft_memcpy(str->data + str->size, s, size);
	str->size += size;
	str->data[str->size] = '\0';
	return (str->data);
}

void	*str_append_n(t_str *str, char *s, size_t n)
{
	const size_t	size = n;

	if (!str->data)
		return (NULL);
	if (str->size + size + 1 > str->capacity)
	{
		str->data = ft_realloc(str->data, str->capacity, str->capacity + size);
		if (!str->data)
			return (NULL);
		str->capacity += size;
	}
	ft_memcpy(str->data + str->size, s, size);
	str->size += size;
	str->data[str->size] = '\0';
	return (str->data);
}

char	str_at(t_str *str, size_t index)
{
	return (str->data[index]);
}

void	str_free(t_str *str)
{
	if (str->data)
		free(str->data);
}
