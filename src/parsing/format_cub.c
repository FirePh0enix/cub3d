/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:44:33 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/27 00:04:01 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

static bool	err_length(int len)
{
	ft_putstr_fd(RED"Error\nA .cub file length should be atleast equal to 4",
		2);
	ft_putstr_fd("\nActual length is"BRED, 2);
	ft_putnbr_fd(len, 2);
	ft_putstr_fd(RESET"\n", 2);
	return (false);
}

static	bool	err_extension(char *str, int i, bool hidden)
{
	ft_putstr_fd(RED"Error\nThe file is not ending with .cub\n", 2);
	ft_putstr_fd(RED"Actual extension: "BRED, 2);
	ft_putstr_fd(str + i, 2);
	if (hidden)
		ft_putstr_fd(" (hidden file)"RESET, 2);
	ft_putstr_fd(RESET"\n", 2);
	return (false);
}

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
	int		len;
	int		i;

	len = ft_strlen(str);
	if (len < 4)
	{
		return (err_length(len));
	}
	i = identify_extension_index(str);
	if (!ft_strcmp(str + i, ".cub") && str[i - 1] && str[i - 1] != '/')
		return (true);
	else
	{
		if (str[i - 1] == '/')
		{
			return (err_extension(str, i, true));
		}
		else
			return (err_extension(str, i, false));
	}
}
