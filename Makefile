# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 20:00:09 by ledelbec          #+#    #+#              #
#    Updated: 2024/06/27 22:31:31 by ledelbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES=\
	src/free.c \
	src/mem.c \
	src/bounding_box.c \
	src/adjust_velocity.c \
	src/raycast.c \
	src/collision.c \
	src/parsing/create_map.c \
	src/parsing/free.c \
	src/parsing/map.c \
	src/parsing/format_cub.c \
	src/parsing/colors.c \
	src/parsing/identifier.c \
	src/parsing/textures.c \
	src/parsing/textures_utils.c \
	src/parsing/player_pos.c \
	src/parsing/parsing_utils.c \
	src/parsing/map_surrounded.c \
	src/parsing/parsing.c \
	src/parsing/textures_msg.c \
	src/parsing/colors_utils.c \
	src/rasterizer/rasterizer.c \
	src/rasterizer/rasterize_triangle.c \
	src/main.c \
	src/input.c \
	src/input_mouse.c \
	src/load.c \
	src/gun.c \
	src/map_free.c \
	src/map.c \
	src/menu.c \
	src/menu_button.c \
	src/menu_text_edit.c \
	src/menu_img.c \
	src/minimap.c \
	src/minimap_utils.c \
	src/minimap_cube.c \
	src/minimap_door.c \
	src/hash.c \
	src/skin.c \
	src/entities/player.c \
	src/entities/player_inputs.c \
	src/entities/fake_player.c \
	src/entities/fake_player_utils.c \
	src/network/serv.c \
	src/network/serv_send.c \
	src/network/serv_send2.c \
	src/network/serv_connect.c \
	src/network/serv_packets.c \
	src/network/serv_utils.c \
	src/network/client.c \
	src/network/client_send.c \
	src/network/client_send2.c \
	src/network/client_packets.c \
	src/network/client_packets2.c \
	src/network/reason.c \
	src/render/init.c \
	src/render/color.c \
	src/render/tga.c \
	src/render/tga_utils.c \
	src/render/font.c \
	src/render/raycast.c \
	src/render/raycast_floor.c \
	src/render/raycast_utils.c \
	src/render/raycast_entity.c \
	src/render/sprite.c \
	src/render/sprite_draw.c

OBJECTS=$(SOURCES:.c=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
NAME=cub3D
CC=clang

OPTS=-O3 -fno-builtin
DEBUG=-g #-fsanitize=address
CFLAGS=-Imlx -Ilibft -MMD $(OPTS) $(DEBUG) -Wall -Wextra #-Werror

all: $(NAME)

-include $(DEPENDENCIES)

libft/libft.a:
	make -C libft

mlx/libmlx.a:
	make -C mlx

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft/libft.a mlx/libmlx.a -lm -lX11 -lXext $(LDFLAGS)

bonus: CFLAGS+=-D_BONUS=1 -D_ENABLE_MULTIPLAYER=1
bonus: $(NAME)

perf: CFLAGS+=-pg
perf: bonus
	./cub3D map3.cub
	gprof cub3D gmon.out > profile.txt

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.o=.d)

fclean: clean
	rm -f cub3d cub3d-ip cub3d-name

re: fclean all
