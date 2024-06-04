# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 20:00:09 by ledelbec          #+#    #+#              #
#    Updated: 2024/06/04 16:13:37 by ledelbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES=\
	src/parsing/format_cub.c \
	src/collision.c \
	src/parsing/colors.c \
	src/parsing/material.c \
	src/parsing/identifier.c \
	src/parsing/textures.c \
	src/parsing/textures_utils.c \
	src/parsing/player_pos.c \
	src/parsing/parsing_utils.c \
	src/parsing/map_surrounded.c \
	src/parsing/parsing.c \
	src/main.c \
	src/map.c \
	src/input.c \
	src/scene.c \
	src/wall.c \
	src/entities/mesh_inst.c \
	src/entities/player.c \
	src/entities/door.c \
	src/gui/panel.c \
	src/network/serv.c \
	src/network/serv_send.c \
	src/network/client.c \
	src/render/init.c \
	src/render/clear.c \
	src/render/framebuffer.c \
	src/render/mesh.c \
	src/render/obj_loader.c \
	src/render/material_loader.c \
	src/render/color.c \
	src/render/tga.c \
	src/render/draw_walls.c \
	src/render/draw_mesh.c \
	src/render/fill_triangle.c \
	src/render/light.c \
	src/render/draw_text.c \
	src/render/gui.c \
	src/render/font.c \

OBJECTS=$(SOURCES:.c=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
NAME=cub3D
CC=clang

OPTS=-O3 -fno-builtin
DEBUG=-g #-fsanitize=address
CFLAGS=-Imlx -Ilibft -g -MMD $(OPTS) $(DEBUG) -Wall -Wextra #-Werror

all: $(NAME)

-include $(DEPENDENCIES)

libft/libft.a:
	make -C libft

mlx/libmlx.a:
	make -C mlx

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft/libft.a mlx/libmlx.a -lm -lX11 -lXext -pthread

bonus: CFLAGS+=-D_BONUS=1 #-D_USE_RENDER_THREAD=1
bonus: $(NAME)

perf: CFLAGS+=-pg
perf: bonus
	./cub3D map2.cub
	gprof cub3D gmon.out > profile.txt

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.o=.d)

fclean: clean
	rm -f cub3d

re: fclean all
