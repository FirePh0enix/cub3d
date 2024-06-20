/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:48:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 18:11:35 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

typedef struct s_alloc			t_alloc;
typedef struct s_alloc_table	t_alloc_table;

# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isspace(int c);

void		*ft_memset(void *p, int c, size_t n);
void		ft_bzero(void *p, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strnstr(const char *big, const char *little, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s, t_alloc_table *at);
char		*ft_strndup(const char *s, size_t n);

int			ft_atoi(const char *s);

void		*ft_calloc(size_t n, size_t size);
void		*ft_realloc(void *p, size_t old_size, size_t size, t_alloc_table *at);

char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strjoin(const char *s1, const char *s2);
char		**ft_split(const char *s, char c, t_alloc_table *at);
char		*ft_itoa(int n);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);

/*
 * Printf functions
 */

int			ft_printf(const char *fmt, ...);
int			ft_sprintf(char *buf, const char *fmt, ...);
int			ft_fprintf(int fd, const char *fmt, ...);

/*
 * get_next_line
 */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char		*realloc_str(char *src, char *buf, int old_size, int n);
int			line_size(char *buf, int bufsize);
char		*get_next_line(int fd);

/*
 * C++ like vector library.
 */

typedef struct s_vecdata
{
	size_t	size;
	size_t	capacity;
	size_t	el_size;
}	t_vecdata;

void	*salloc(t_alloc_table *at, size_t n);

void		*ft_vector(size_t el_size, size_t capacity, t_alloc_table *at);
/*
 * Free the memory used by the vector. `vec` should be the vector itself.
 */
void		ft_vector_free(void *vec);
/*
 * Reset the size of the vector but does not free anything.
 */
void		ft_vector_clear(void *vec);
/*
 * Like `ft_vector_free` but it will also free each elements of the vector
 * assuming the vector is storing pointers.
 */
void		ft_vector_deep_free(void *vec);
/*
 * Add an element at the end of the vector. `elp` is the address of the element
 * to add.
 * `vec` is the address of the vector and not the vector itself, same for all
 * add*, del* functions.
 * The function returns the new address of the vector data or `NULL` if the
 * reallocation failed.
 */
void		*ft_vector_add(void *vec, void *elp, t_alloc_table *at);
/*
 * Delete the element at `index`. After deletion the order of the remaining
 * elements is preserved.
 */
void		ft_vector_del(void *vec, size_t index);
/*
 * Delete the element at `index`. A less costly version of ft_vector_del but it
 * does not preserve the order of elements.
 */
void		ft_vector_del_swap(void *vec, size_t index);
size_t		ft_vector_size(void *vec);
/*
 * Apply the function `f` on all elements of the vector.
 */
void		ft_vector_iter(void *vec, void (*f)(void*));
/*
 * Create a new vector from an existing array of string.
 */
char		**ft_vector_from_array(char *array[], size_t count);

t_vecdata	*ft_vector_data(void *vec);

/*
 * String manipulation
 */

typedef struct s_str
{
	char	*data;
	size_t	size;
	size_t	capacity;
}	t_str;

t_str		str(char *s);
void		*str_append(t_str *str, char *s);
void		*str_append_n(t_str *str, char *s, size_t n);
char		str_at(t_str *str, size_t index);
void		str_free(t_str *str);

t_str		str_null(void);

#endif
