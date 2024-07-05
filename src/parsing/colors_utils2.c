/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:06:17 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/05 17:34:16 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

bool	count_rgb(char *color)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(color))
	{
		if (color[i] && color[i] == ',' && ft_isdigit(color[i + 1]))
			count++;
		++i;
	}
	if (count != 2)
	{
		ft_printf(RED"Error\nAn RGB color should contain ");
		ft_printf("3 values separated by commas.\n"RESET);
		return (false);
	}
	return (true);
}
