/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:22 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/14 15:57:37 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

int	calc_map_height(char **maps)
{
	int	i;
	int	height;

	i = 6;
	height = 0;
	while (maps[i])
	{
		height++;
		++i;
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
