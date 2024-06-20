/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:03:05 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/22 13:23:31 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	len;
	int	strlen;
	int	index;

	if (*to_find == 0)
		return (str);
	index = 0;
	strlen = ft_strlen(str);
	len = ft_strlen(to_find);
	while (str[index] && index < strlen - len + 1)
	{
		if (ft_strncmp(str + index, to_find, len) == 0)
			return (str + index);
		index++;
	}
	return ((char *)0);
}
