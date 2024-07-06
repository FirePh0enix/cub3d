/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:55:49 by vopekdas          #+#    #+#             */
/*   Updated: 2024/07/06 19:03:13 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

// ---------------------------------------------------------------------------//
//	+	+	+	+	+	+	+	// LIBRARIES //	+	+	+	+	+	+	+ 	+ //
// ---------------------------------------------------------------------------//

# include <stdbool.h>
# include "../render/render.h"

// ---------------------------------------------------------------------------//
//	+	+	+	+	+	+	+	// COLORS //	+	+	+	+	+	+	+ 	+ //
// ---------------------------------------------------------------------------//

# define YELLOW	"\033[0;33m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define RED	"\033[0;31m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define BLACK	"\033[0;30"
# define WHITE	"\033[0;37m"
# define RESET "\033[0m"

# define BYELLOW	"\033[1;33m"
# define BGREEN		"\033[1;32m"
# define BBLUE		"\033[1;34m"
# define BRED		"\033[1;31m"
# define BPURPLE	"\033[1;35m"
# define BCYAN		"\033[1;36m"
# define BBLACK		"\033[1;30m"
# define BWHITE		"\033[1;37m"

// ---------------------------------------------------------------------------//
//	+	+	+	+	+	+	+	// STRUCTURES //	+	+	+	+	+	+	+ //
// ---------------------------------------------------------------------------//
typedef struct s_map	t_map;

// ---------------------------------------------------------------------------//
//	+	+	+	+	+	+	+	// CONSTANTS //	+	+	+	+	+	+	+ 	+ //
// ---------------------------------------------------------------------------//
# define EPSILON 1e-1

// ---------------------------------------------------------------------------//
//	+	+	+	+	+	+	+	// FUNCTIONS //	+	+	+	+	+	+	+ 	+ //
// ---------------------------------------------------------------------------//

//############################################################################//
								// COLORS CREATION //
//############################################################################//
int		ft_nblen(int nb);
bool	is_rgb_range(char *s);
void	fill_color(char *identifier, t_map *map, unsigned char color, int i);

//############################################################################//
								// MAP //
//############################################################################//
char	**create_map(char **cub_file, t_map *map, t_alloc_table *at);
char	**map_space(char **map, size_t width, size_t height, t_alloc_table *at);
int		calc_map_height(char **maps);
int		calc_map_max_width(char **maps);
bool	map_to_tiles(t_map *map, char **maps, t_alloc_table *at);

//############################################################################//
								// ERROR MESSAGE //
//############################################################################//
void	putstr_sep(char *str, char n);
bool	err_textures(char *identifier);
bool	err_identifier(char *identifier);
//############################################################################//
					// IDENTIFIER VALIDATION AND DETECTION //
//############################################################################//
bool	is_valid_identifier_color(char *str);
bool	is_valid_identifier_text(char *str);
bool	is_valid_char_in_map(char **maps, t_map *map);
bool	is_map_surrounded(char **maps, t_map *map);
bool	is_valid_rgb(t_map *map, char **map_config, t_alloc_table *at);
bool	is_valid_file_name(char *str);
char	*detect_identifier(char *texture);
char	*texture_path(char *path);

//############################################################################//
								// TEXTURES //
//############################################################################//
void	assign_textures(char *identifier, t_map *map, t_image *image);
t_image	*load_texture(char *textures, char *identifier, t_alloc_table *at);
bool	fill_texture(t_map *map, char **maps, t_alloc_table *at);

//############################################################################//
								// PLAYER //
//############################################################################//
bool	find_player_pos(char **maps, t_map *map);

//############################################################################//
								// UTILS //
//############################################################################//
char	*read_to_string(char *filename, t_alloc_table *at);
bool	free_identifier(char *identifier);
bool	check_enough_line(char **map_config);

#endif