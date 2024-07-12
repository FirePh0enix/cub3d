/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:05:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/07/12 11:15:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "libft.h"
#include <stdlib.h>

void	*salloc(t_alloc_table *at, size_t n)
{
	void	*ptr;
	t_alloc	*alloc;
	t_alloc	*it;

	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	alloc = malloc(sizeof(t_alloc));
	if (!alloc)
		return (free(ptr), NULL);
	alloc->ptr = ptr;
	alloc->next = NULL;
	if (!at->first)
	{
		at->first = alloc;
		return (ptr);
	}
	it = at->first;
	while (it->next)
		it = it->next;
	it->next = alloc;
	return (ptr);
}

void	*scalloc(t_alloc_table *at, size_t size, size_t n)
{
	void	*ptr;
	t_alloc	*alloc;
	t_alloc	*it;

	ptr = ft_calloc(n, size);
	if (!ptr)
		return (NULL);
	alloc = malloc(sizeof(t_alloc));
	if (!alloc)
		return (free(ptr), NULL);
	alloc->ptr = ptr;
	alloc->next = NULL;
	if (!at->first)
	{
		at->first = alloc;
		return (ptr);
	}
	it = at->first;
	while (it->next)
		it = it->next;
	it->next = alloc;
	return (ptr);
}

void	sfreeall(t_alloc_table *at)
{
	t_alloc	*it;
	t_alloc	*next;

	it = at->first;
	while (it)
	{
		next = it->next;
		free(it->ptr);
		free(it);
		it = next;
	}
}

void	sfree(t_alloc_table *at, void *p)
{
	t_alloc	*it;
	t_alloc	*prev;
	t_alloc	*next;

	if (at->first->ptr == p)
	{
		next = at->first->next;
		free(p);
		free(at->first);
		at->first = next;
		return ;
	}
	it = at->first;
	while (it->ptr != p)
	{
		it = it->next;
		prev = it;
	}
	if (it)
	{
		next = it->next;
		free(it->ptr);
		free(it);
		prev->next = next;
	}
}
