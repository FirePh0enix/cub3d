/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:55:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 15:57:31 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

char	*detect_identifier(char *texture)
{
	int		i;
	char	*identifier;

	i = 0;
	identifier = NULL;
	identifier = ft_calloc(ft_strlen(texture) + 1, 1);
	if (!identifier)
	{
		ft_putstr_fd("Error\nIdentifier malloc failed\n", 2);
		return (NULL);
	}
	while (texture[i])
	{
		if (texture[i] != ' ')
		{
			identifier[i] = texture[i];
			++i;
		}
		else
			break ;
	}
	return (identifier);
}

bool	is_valid_identifier_text(char *str)
{
	if (!ft_strcmp(str, "NO"))
		return (true);
	else if (!ft_strcmp(str, "SO"))
		return (true);
	else if (!ft_strcmp(str, "WE"))
		return (true);
	else if (!ft_strcmp(str, "EA"))
		return (true);
	else
		return (false);
}

bool	is_valid_identifier_color(char *str)
{
	if (!ft_strcmp(str, "F"))
		return (true);
	else if (!ft_strcmp(str, "C"))
		return (true);
	else
		return (false);
}

