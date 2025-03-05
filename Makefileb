# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 15:02:36 by dsamuel           #+#    #+#              #
#    Updated: 2025/02/28 12:25:26 by baguiar-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

# Compiler and compilation flags
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -g3 #-fsanitize=address

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH = ./sources/
SRC		= 	main.c \
			error.c \
			init/init_data.c \
			init/init_mlx.c \
			init/init_textures.c \
			parsing/check_args.c \
			parsing/parse_data.c \
			parsing/get_file_data.c \
			parsing/create_game_map.c \
			parsing/check_textures.c \
			parsing/check_map.c \
			parsing/check_map_borders.c \
			parsing/fill_color_textures.c \
			parsing/parsing_utils.c \
			movement/input_handler.c \
			movement/player_dir.c \
			movement/player_pos.c \
			movement/player_move.c \
			movement/player_rotate.c \
			render/raycasting.c \
			render/render.c \
			render/texture.c \
			render/image_utils.c \
			render/minimap_render.c \
			render/minimap_image.c \
			exit/exit.c \
			exit/free_data.c \
			debug/debug.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Clone minilibx-linux repository if it doesn't exist
$(MLX_PATH):
	git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux
	git submodule update --init --recursive

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/init
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/movement
	mkdir -p $(OBJ_PATH)/render
	mkdir -p $(OBJ_PATH)/debug
	mkdir -p $(OBJ_PATH)/exit

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

# Libft rule
$(LIBFT):
	make -sC $(LIBFT_PATH)

# MLX rule
$(MLX): $(MLX_PATH)
	make -sC $(MLX_PATH)

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	@if [ -d "minilibx-linux" ]; then \
		make -C $(MLX_PATH) clean; \
	fi
	

# Remove program executable and minilibx-linux repository
fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)
	make -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all

.PHONY: all re clean fclean bonus
