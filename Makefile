
NAME = cub3d

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

MLX_DIR = includes/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
INCLUDES = -I$(MLX_DIR)

SRC = src/main.c \
	  src/player.c
	  
OBJ = $(SRC:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS) $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(MLX_DIR) clean

re: all fclean