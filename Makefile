
NAME = cub3d

CC = cc
RM = rm - rf

LFLAGS = -L./includes/mlx -lmlx -lXext -lX11 -lm -lz
INCLUDES = includes/mlx/libmlx.a

SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC)

fclean: 
	$(RM) $(OBJ)
	$(RM) $(NAME)