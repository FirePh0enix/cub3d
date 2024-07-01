/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:24:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/01 11:43:21 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static char	*which_ident_miss(int f, int c)
{
	if (f == 0)
		return ("F");
	else if (c == 0)
		return ("C");
	return (0);
}

static	bool	check_number_fc(int f, int c)
{
	char	*miss_ident;

	if (f != 1 || c != 1)
	{
		miss_ident = which_ident_miss(f, c);
		ft_putstr_fd(RED"Error\n", 2);
		ft_putstr_fd("Identifier "BRED, 2);
		ft_putstr_fd(miss_ident, 2);
		ft_putstr_fd(RED" is missing (only the first two ", 2);
		ft_putstr_fd("identifiers are processed)\n"RESET, 2);
		return (false);
	}
	return (true);
}

bool	is_valid_number_fc(char **textures)
{
	int		i;
	int		f;
	int		c;
	char	*identifier;

	i = 3;
	c = 0;
	f = 0;
	while (++i < 6)
	{
		identifier = detect_identifier(textures[i]);
		if (!identifier)
			return (false);
		if (is_valid_identifier_color(identifier))
		{
			if (!ft_strcmp("C", identifier))
				c++;
			else if (!ft_strcmp("F", identifier))
				f++;
		}
		free(identifier);
	}
	return (check_number_fc(f, c));
}

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
		ft_putstr_fd(RED"Error\nThere is too many coma for an RGB\n"RESET, 2);
	return (n);
}
