/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:16:57 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/11 23:53:03 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parsing/parsing.h"

bool	err_textures(char *identifier)
{
	ft_putstr_fd(RED"Error\n"BRED, 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(RED" has not been created\n"RESET, 2);
	free_identifier(identifier);
	return (false);
}
