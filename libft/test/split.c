/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:58:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/05 18:04:00 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	test_split(void)
{
	char	**strs;
	int		i;

	strs = ft_split(",,,", ',');
	i = 0;
	while (strs[i])
	{
		ft_printf("Part: `%s`\n", strs[i]);
		i++;
	}
	ft_printf("End of output\n");
}
