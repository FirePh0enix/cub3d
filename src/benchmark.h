/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:28:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/01 22:35:44 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_H
# define BENCHMARK_H

# include <time.h>

# define BENCH(NAME, FN) \
	do {                                                                          \
		clock_t	__start = clock();                                                \
		FN;                                                                       \
		clock_t	__elapsed = clock() - __start;                                    \
		printf("%s | Time taken %lf ms\n", #NAME, ((double)__elapsed / CLOCKS_PER_SEC) * 1000.0); \
	} while (0)

#endif
