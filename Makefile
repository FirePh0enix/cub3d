# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 20:00:09 by ledelbec          #+#    #+#              #
#    Updated: 2024/03/31 23:22:48 by ledelbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES=\
	src/main.c \
	src/gui/panel.c \
	src/render/init.c \
	src/render/clear.c \
	src/render/mesh.c \
	src/render/obj_loader.c \
	src/render/material_loader.c \
	src/render/color.c \
	src/render/ppm.c \
	src/render/tga.c \
	src/render/draw_walls.c \
	src/render/draw_mesh.c \
	src/render/fill_triangle.c \
	src/render/draw_text.c \
	src/render/gui.c \
	src/render/font.c \

OBJECTS=$(SOURCES:.c=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
NAME=cub3D
CC=clang

OPTS=-O2 -fno-builtin
CFLAGS=-Imlx -Ilibft -MMD -g3 $(OPTS) -Wall -Wextra #-Werror

ifdef RTHREADS

# Enable multithreading in the renderer.

CFLAGS+=-pthread -DRTHREADS
SOURCES+=\
	src/render/mt.c

endif

all: $(NAME)

-include $(DEPENDENCIES)

libft/libft.a:
	make -C libft

mlx/libmlx.a:
	make -C mlx

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft/libft.a mlx/libmlx.a -lm -lX11 -lXext

perf: CFLAGS+=-pg
perf: $(OBJECTS) mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft/libft.a mlx/libmlx.a -lm -lX11 -lXext
	./cub3D
	gprof cub3D gmon.out > profile.txt

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.o=.d)

fclean: clean
	rm -f cub3d

re: fclean all
