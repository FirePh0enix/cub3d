/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:22 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/12 11:20:17 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

bool	valid_id(char *identifier, char *map_conf)
{
	if (!ft_strcmp(identifier, "NO"))
		return (true);
	else if (!ft_strcmp(identifier, "SO"))
		return (true);
	else if (!ft_strcmp(identifier, "WE"))
		return (true);
	else if (!ft_strcmp(identifier, "EA"))
		return (true);
	else if (!ft_strcmp(identifier, "F"))
		return (true);
	else if (!ft_strcmp(identifier, "C"))
		return (true);
	else if (ft_strlen(map_conf) == 0)
		return (true);
	return (false);
}

int	skip_until_map(char **map_conf)
{
	int		i;
	char	*identifier;

	i = 0;
	while (map_conf[i])
	{
		identifier = detect_identifier(map_conf[i]);
		if (!identifier)
			return (-1);
		if (valid_id(identifier, map_conf[i]))
		{
			free(identifier);
			++i;
		}
		else
		{
			free(identifier);
			break ;
		}
	}
	return (i);
}

int	calc_map_height(char **maps)
{
	int	i;
	int	height;

	i = skip_until_map(maps);
	if (i == -1)
		return (-1);
	height = 0;
	while (maps[i])
	{
		height++;
		i++;
	}
	return (height);
}

int	calc_map_max_width(char **maps)
{
	int	i;
	int	final_len;
	int	len;

	i = 0;
	final_len = 0;
	len = 0;
	while (maps[i])
	{
		len = ft_strlen(maps[i]);
		if (final_len < len)
			final_len = len;
		++i;
	}
	return (final_len);
}
