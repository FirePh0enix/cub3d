/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:28:24 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/15 12:09:36 by ledelbec         ###   ########.fr       */
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

typedef struct s_benchslot
{
	const char	*name;
	clock_t		cumulative;
	size_t		count;
}	t_benchslot;

static inline t_benchslot *_search_slot(
		t_benchslot *slots,
		size_t num,
		const char *name)
{
	for (size_t i = 0; i < num; i++)
		if (slots[i].name != NULL && strcmp(slots[i].name, name) == 0)
			return (slots + i);
	return (NULL);
}

static inline void	_init_slot(
		t_benchslot *slots,
		size_t num,
		const char *name)
{
	for (size_t i = 0; i < num; i++)
		if (slots[i].name == NULL)
		{
			slots[i].name = name;
			break;
		}
}

static inline void	_dumps_bench(t_benchslot *slots, size_t num)
{
	printf("\b\b");
	for (size_t i = 0; i < num; i++)
	{
		if (slots[i].name == NULL)
			break;
		printf("\b");
	}
	printf("\nBenchmark results:\n");
	for (size_t i = 0; i < num; i++)
	{
		if (slots[i].name == NULL)
			break;
		printf("%s | Avg time taken: %f ms\n",
				slots[i].name, (float)((slots[i].cumulative )));
		slots[i].cumulative = 0;
		slots[i].count = 0;
	}
}

# define BENCH_GLOBAL_INIT(NAME, NUM) \
	t_benchslot	NAME[NUM]; \
	size_t		NAME##_size = NUM;

# define BENCH_INIT(BENCH, SLOT)             \
	do {                                     \
		extern t_benchslot	BENCH[];            \
		extern size_t		BENCH ## _size;       \
		_init_slot(BENCH, BENCH##_size, #SLOT); \
	} while (0)

# define BENCH_FUNC(BENCH, SLOT, EXPR) \
	do { \
		extern t_benchslot	BENCH[];      \
		extern size_t		BENCH##_size; \
		clock_t	__start = clock();     \
		EXPR;                          \
		clock_t	__end = clock();       \
		t_benchslot	*__slot = _search_slot(BENCH, BENCH##_size, #SLOT); \
		__slot->cumulative += ((__end - __start) / CLOCKS_PER_SEC) * 1000.0; \
		__slot->count += 1; \
	} while (0)

# define BENCH_DUMPS(BENCH)                \
	do {                                   \
		extern t_benchslot	BENCH[];       \
		extern size_t		BENCH##_size;  \
		_dumps_bench(BENCH, BENCH##_size); \
	} while (0)
	

#endif
