/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:07:17 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 18:34:02 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = salloc(at, ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}
