#include "../cub3d.h"
#include "../parsing/parsing.h"

static	bool	error_char(char c, int y, int x)
{
	ft_putstr_fd(RED"Error\n"BRED, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(RED" is not a valid character at ", 2);
	ft_putstr_fd(BRED"[", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd("]\n"RESET, 2);
	return (false);
}

static bool	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'D')
		return (true);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	else
		return (false);
}

bool	is_valid_char_in_map(char **maps, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (maps[y][x] && !is_valid_char(maps[y][x]))
			{
				return (error_char(maps[y][x], y, x));
			}
			++x;
		}
		++y;
	}
	return (true);
}
