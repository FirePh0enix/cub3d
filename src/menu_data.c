/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:37:14 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/01 20:00:41 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "cub3d.h"
#include <fcntl.h>

void	save_data(t_menu *menu)
{
	int	fd;

	fd = open("cub3d-ip", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (write(fd, menu->ip.buffer, menu->ip.len) == -1)
		return ;
	close(fd);
	fd = open("cub3d-name", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (write(fd, menu->name.buffer, menu->name.len) == -1)
		return ;
	close(fd);
}

static size_t	strlen_max(char *s, size_t len)
{
	size_t	strlen;

	strlen = ft_strlen(s);
	if (strlen > len)
		return (len);
	return (strlen);
}

void	load_data(t_menu *menu, t_alloc_table *at)
{
	char	*s;

	s = read_to_string("cub3d-ip", at);
	if (s)
	{
		ft_bzero(menu->ip.buffer, 16);
		ft_memcpy(menu->ip.buffer, s, strlen_max(s, 16));
		menu->ip.buffer[strlen_max(s, 16)] = '\0';
		menu->ip.len = ft_strlen(menu->ip.buffer);
	}
	s = read_to_string("cub3d-name", at);
	if (s)
	{
		ft_bzero(menu->name.buffer, 16);
		ft_memcpy(menu->name.buffer, s, strlen_max(s, 16));
		menu->name.buffer[strlen_max(s, 16)] = '\0';
		menu->name.len = ft_strlen(menu->name.buffer);
	}
}
