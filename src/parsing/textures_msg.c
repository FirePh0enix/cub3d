/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:16:57 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/22 16:17:28 by vopekdas         ###   ########.fr       */
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

bool	err_identifier(char *identifier)
{
	ft_putstr_fd(RED"Error\n", 2);
	ft_putstr_fd("Wrong identifier: "BRED, 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd(RED"\nIdentifier should be: "BRED, 2);
	ft_putstr_fd("NO | SO | WE | EA\n"RESET, 2);
	free_identifier(identifier);
	return (false);
}
