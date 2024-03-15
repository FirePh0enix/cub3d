/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:15:48 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/15 16:22:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include <stdlib.h>

static char *read_to_string(const char *filename) {
  int fd;
  char *str;
  char buffer[4096];
  int str_size;
  int n;

  fd = open(filename, O_RDONLY);
  if (fd == -1)
    return (NULL);
  str = NULL;
  str_size = 0;
  n = 4096;
  while (n == 4096) {
    n = read(fd, buffer, 4096);
    if (n == -1)
      return (NULL);
    str = realloc(str, /*str_size + 1,*/ str_size + n + 1);
    if (!str)
      return (close(fd), NULL);
    ft_memcpy(str + str_size, buffer, n);
    str[str_size + n] = '\0';
    str_size += n;
  }
  return (close(fd), str);
}

/*
 * Convert a path like `/home/ldelbec/Downloads/some_image.png` to
 * `some_image.xpm`.
 */
static void convert_path(char *in, char *out) {
  const size_t sz = ft_strlen(in);
  size_t i;
  size_t j;

  // FIXME Might not work if path does not contains `/`
  i = sz - 1;
  while (i > 0) {
    if (in[i] == '/')
      break;
    i--;
  }
  i++;
  j = 0;
  while (i < sz + 1)
    out[j++] = in[i++];
  // FIXME Can segfault is out size < 3
  out[j - 3] = 'x';
  out[j - 2] = 'p';
  out[j - 1] = 'm';
}

t_material	*material_load(char *name)
{
	const char	*str = read_to_string(name);
	char		**lines;
	char		*part;
	t_material	*material;
	char		texture[32];

	// printf("%s\n", name);
	if (!str)
		return (NULL);
	material = malloc(sizeof(t_material));
	lines = ft_split(str, '\n');
	while (*lines)
	{
    	part = strtok(*lines, " ");
    	if (part == NULL || part[0] == 0 || ft_strcmp(part, "map_Kd"))
		{
			lines++;
			continue;
		}
		part = strtok(NULL, " ");
		convert_path(part, texture);
		lines++;
	}
	//printf("Texture name: %s\n", texture);
	return (material);
}
