/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:28:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/02 14:18:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_H
# define BENCHMARK_H

# include <time.h>

# define BENCH(NAME, FN, ITER) \
	do {                                                                          \
		clock_t	__start = clock();                                                \
		for (int i = 0; i < ITER; i++) \
			FN;                                                                       \
		clock_t	__elapsed = clock() - __start;                                    \
		printf("%s | Avg time taken %lf ms\n", #NAME, (((double)__elapsed / CLOCKS_PER_SEC) * 1000.0) / ITER); \
	} while (0)

#endif
