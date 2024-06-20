/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:10:07 by ledelbec          #+#    #+#             */
/*   Updated: 2024/04/09 14:44:46 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf_int.h"
#include <stdarg.h>
#include <unistd.h>

static int	_printf_write(t_writer *w, const char *s, int len)
{
	(void) w;
	return (write(w->fd, s, len));
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	int			n;
	va_list		list;
	t_writer	writer;

	va_start(list, fmt);
	writer = (t_writer){_printf_write, NULL, fd};
	n = format(fmt, list, &writer);
	va_end(list);
	return (n);
}

int	ft_printf(const char *fmt, ...)
{
	int			n;
	va_list		list;
	t_writer	writer;

	va_start(list, fmt);
	writer = (t_writer){_printf_write, NULL, 1};
	n = format(fmt, list, &writer);
	va_end(list);
	return (n);
}

static int	_sprintf_write(t_writer *w, const char *s, int len)
{
	ft_memcpy(w->p, s, len);
	w->p += len;
	return (len);
}

int	ft_sprintf(char *buf, const char *fmt, ...)
{
	int			n;
	va_list		list;
	t_writer	writer;

	va_start(list, fmt);
	writer = (t_writer){_sprintf_write, buf, -1};
	n = format(fmt, list, &writer);
	((char *) writer.p)[0] = '\0';
	va_end(list);
	return (n);
}
