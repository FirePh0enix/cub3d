# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 20:00:09 by ledelbec          #+#    #+#              #
#    Updated: 2024/03/01 00:40:41 by ledelbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES=\
	src/main.c \
	src/math/v3_basic.c \
	src/math/v3_complex.c \
	src/render/init.c \
	src/render/mesh.c \
	src/render/draw_mesh.c \

OBJECTS=$(SOURCES:.c=.o)
NAME=cub3d
CC=clang
CFLAGS=-Imlx -MMD -g3 -Wall -Wextra #-Werror

all: $(NAME)

-include $(OBJECTS:.o=.d)

mlx/libmlx.a:
	make -C mlx

$(NAME): $(OBJECTS) mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) mlx/libmlx.a -lm -lX11 -lXext

perf: CFLAGS+=-pg
perf: $(OBJECTS) mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) mlx/libmlx.a -lm -lX11 -lXext
	./cub3d
	gprof cub3d gmon.out > profile.txt

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.c=.d)

fclean: clean
	rm -f cub3d

re: fclean all
