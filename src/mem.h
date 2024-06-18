/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:55:59 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/18 16:08:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include <stddef.h>

typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}	t_alloc;

typedef struct s_alloc_table
{
	t_alloc	*first;
}	t_alloc_table;

void	*salloc(t_alloc_table *at, size_t n);
void	*scalloc(t_alloc_table *at, size_t n, size_t size);
void	sfreeall(t_alloc_table *at);

#endif
