/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:24:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/07 16:31:23 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"
#include <stdbool.h>

size_t	ft_countchr(char *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		if (*s == c)
			n++;
		s++;
	}
	if (n != 2)
		ft_fprintf(2,
			RED"Error\nIncorrect number of commas for an RGB value; exactly "
			BRED"2"RED" are required.\n"RESET);
	return (n);
}

bool	error_rgb(t_count *count)
{
	if (count->identifier_count != 2)
	{
		ft_fprintf(2,
			RED"Error\nExactly 2 RGB color identifiers are expected.\nFound: "
			BRED"%d "RED"instead.\n"RESET,
			count->identifier_count);
		return (false);
	}
	if (count->f != 1 || count->c != 1)
	{
		ft_fprintf(2,
			RED"Error\nExactly one RGB value is expected for both floor and ce"
			"iling.\nFound: "
			BRED"%d"RED" for floor and "BRED"%d"RED" for ceiling.\n"RESET,
			count->f, count->c);
		return (false);
	}
	return (true);
}

void	count_fc(char *identifier, int *f, int *c, int *identifier_count)
{
	if (!ft_strcmp(identifier, "F"))
		(*f)++;
	else if (!ft_strcmp(identifier, "C"))
		(*c)++;
	(*identifier_count)++;
}
