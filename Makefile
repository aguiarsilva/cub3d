# Makefile for Cub3D project

NAME = cub3d

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)

# Directories
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# MinilibX flags (for Linux)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Source files
SRCS = main.c \
	   map_parser.c \
	   texture_loader.c \
	   cleaner.c \
	   raycast.c

# Object files
OBJS = $(SRCS:.c=.o)

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: $(MLX) $(LIBFT) $(NAME)

# Rule for building the executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Building $(NAME)...$(NC)"
	$(CC) $(OBJS) -o $(NAME) $(LIBFT) $(MLX_FLAGS)
	@echo "$(GREEN)Build complete!$(NC)"

# Rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for building MinilibX
$(MLX):
	@echo "$(GREEN)Building MinilibX...$(NC)"
	@make -C $(MLX_DIR)

# Rule for building libft
$(LIBFT):
	@echo "$(GREEN)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning executable and libraries...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(MLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re