/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reason.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:36:50 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/24 22:56:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"

char	*reason_str(t_reason reason)
{
	if (reason == REASON_INVALID_HASH)
		return ("Invalid executable hash, are you trying to cheat ?");
	else if (reason == REASON_INVALID_MAP)
		return ("Invalid map selected");
	return ("unknown2");
}
