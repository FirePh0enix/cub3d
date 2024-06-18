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
	else if (_BONUS && ft_isdigit(c))
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

static	bool	err_floor_and_ceilling(void)
{
	ft_putstr_fd(RED"Error\n", 2);
	ft_putstr_fd("You need to add "BRED, 2);
	ft_putstr_fd("floor ", 2);
	ft_putstr_fd(RED"and "BRED, 2);
	ft_putstr_fd("ceilling", 2);
	ft_putstr_fd(RED" colors\n"RESET, 2);
	return (false);
}

bool	check_enough_line(char **map_file)
{
	int	i;

	i = 0;
	while (map_file[i])
		++i;
	if (i < 4)
	{
		ft_putstr_fd(RED"Error\n", 2);
		ft_putstr_fd("You need to add "BRED, 2);
		ft_putstr_fd("4 textures\n"RESET, 2);
		return (false);
	}
	else if (i < 6)
	{
		return (err_floor_and_ceilling());
	}
	else if (i < 7)
	{
		ft_putstr_fd(RED"Error\n", 2);
		ft_putstr_fd("You need to add a "BRED, 2);
		ft_putstr_fd("map\n"RESET, 2);
		return (false);
	}
	return (true);
}
