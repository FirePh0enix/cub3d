/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:44:33 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/04 15:16:58 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	identify_extension_index(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (str[i] && i > 0)
	{
		if (str[i] == '.')
			break ;
		--i;
	}
	return (i);
}

bool	is_valid_file_name(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	if (len < 4)
	{
		printf(RED"ERROR\nA .CUB FILE LENGTH SHOULD BE ATLEAST EQUAL TO 4\n");
		printf("ACTUAL LENGTH IS %d\n"RESET, len);
		return (false);
	}
	i = identify_extension_index(str);
	if (!ft_strcmp(str + i, ".cub") && str[i - 1] && str[i - 1] != '/')
		return (true);
	else
	{
		if (str[i - 1] == '/')
		{
			printf("\033[1;31m"RED"ERROR\nTHE FILE IS NOT ENDING WITH .CUB\n");
			printf(RED"ACTUAL EXTENSION: %s (hidden file)\n"RESET, str + i);
			return (false);
		}
		printf("\033[1;31m"RED"ERROR\nTHE FILE IS NOT ENDING WITH .CUB\n");
		printf(RED"ACTUAL EXTENSION: %s\n"RESET, str + i);
		return (false);
	}
}
