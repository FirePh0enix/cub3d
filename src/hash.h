/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:44:33 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/24 19:51:22 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include <stddef.h>
# include <stdint.h>

/*
	Quick and easy hash function.
 */
uint32_t	fnv32_hash(const char *str, size_t len);

/*
	Helper to hash an entire file.
 */
uint32_t	fnv32_hash_file(char *file);

#endif
