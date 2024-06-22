/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:57:41 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/08 01:16:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_int.h"

bool	isflag(char c)
{
	return (c == 'd' || c == 'i' || c == 'x' || c == 'x' || c == 'c'
		|| c == 's' || c == '%' || c == 'p' || c == 'u');
}