/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:28:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/19 23:11:49 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_H
# define BENCHMARK_H

# include <sys/select.h>
# include <time.h>
# include <string.h>
# include <stdio.h>

/*
 * TODO This should be removed before correcting the project !!
 */

# define BENCH_FUNC(NAME, EXPR) \
	do { \
		clock_t	__start = clock();     \
		EXPR;                          \
		clock_t	__end = clock();       \
		printf("%s | Time taken: %f ms\n", #NAME, ((float)(__end - __start) / CLOCKS_PER_SEC) * 1000.0); \
	} while (0)

#endif
