/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:38:47 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/28 00:01:50 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*realloc_str(char *src, char *buf, int old_size, int n)
{
	char	*cpy;
	int		i;

	cpy = malloc(old_size + n + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		cpy[i] = src[i];
		i++;
	}
	if (src)
		free(src);
	i = 0;
	while (i < n)
	{
		cpy[old_size + i] = buf[i];
		i++;
	}
	cpy[old_size + i] = '\0';
	return (cpy);
}

int	line_size(char *buf, int bufsize)
{
	int	len;

	len = 0;
	while (buf[len] && buf[len] != '\n' && len < bufsize)
		len++;
	if (len < bufsize && buf[len] == '\n')
		len++;
	return (len);
}
