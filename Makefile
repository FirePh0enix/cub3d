# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 20:00:09 by ledelbec          #+#    #+#              #
#    Updated: 2024/06/20 13:25:55 by ledelbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES=\
	src/parsing/create_map.c \
	src/parsing/free.c \
	src/parsing/map.c \
	src/bounding_box.c \
	src/adjust_velocity.c \
	src/raycast.c \
	src/parsing/format_cub.c \
	src/collision.c \
	src/parsing/colors.c \
	src/parsing/identifier.c \
	src/parsing/textures.c \
	src/parsing/textures_utils.c \
	src/parsing/player_pos.c \
	src/parsing/parsing_utils.c \
	src/parsing/map_surrounded.c \
	src/parsing/parsing.c \
	src/parsing/colors_utils.c \
	src/rasterizer/rasterizer.c \
	src/rasterizer/rasterize_triangle.c \
	src/resource_gen.c \
	src/main.c \
	src/input.c \
	src/scene.c \
	src/scene_update.c \
	src/load.c \
	src/gun.c \
	src/menu.c \
	src/menu_button.c \
	src/menu_text_edit.c \
	src/menu_img.c \
	src/minimap.c \
	src/sound/sound.c \
	src/entities/player.c \
	src/entities/fake_player.c \
	src/network/serv.c \
	src/network/serv_send.c \
	src/network/client.c \
	src/render/init.c \
	src/render/color.c \
	src/render/tga.c \
	src/render/font.c \
	src/render/raycast.c \
	src/render/sprite.c

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

bonus: CFLAGS+=-D_BONUS=1 -D_ENABLE_MULTIPLAYER=1 -D_ENABLE_SOUND=1
bonus: LDFLAGS+=-lpulse -lpulse-simple -pthread
bonus: $(NAME)

res:
	./tools/resource.py

perf: CFLAGS+=-pg
perf: bonus
	./cub3D map3.cub
	gprof cub3D gmon.out > profile.txt

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.o=.d)

fclean: clean
	rm -f cub3d cub3d-ip cub3d-name

re: fclean all

# Main Menu    - https://www.youtube.com/watch?v=_WnP1wKxW4M
# BFG Division - https://www.youtube.com/watch?v=QHRuTYtSbJQ

yt-dlp:
	wget https://github.com/yt-dlp/yt-dlp/releases/download/2024.05.27/yt-dlp_linux -O yt-dlp
	chmod +x yt-dlp

menu.wav:
	./yt-dlp -x --audio-format wav https://www.youtube.com/watch?v=_WnP1wKxW4M -o menu.wav

bfg.wav:
	./yt-dlp -x --audio-format wav https://www.youtube.com/watch?v=QHRuTYtSbJQ -o bfg.wav

music: yt-dlp menu.wav bfg.wav
