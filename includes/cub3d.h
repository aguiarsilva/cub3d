

#ifndef CUB3D_H
# define CUB3D_H

# define HEIGHT 720
# define WIDTH 1280
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359


#include "../includes/minilibx-linux/mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_player
{
    float   x;
    float   y;
    float   angle;

    bool    key_up;
    bool    key_down;
    bool    key_left;
    bool    key_right;
    bool    left_rotate;
    bool    right_rotate;
    
}   t_player;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    void        *img;

    char        *data;
    int         bpp;
    int         line_size;
    int         endian;
    t_player    player;

    char        **map;
    
}   t_game;

void    player_init(t_player *player);
int     key_press(int keycode, t_player *player);
int     key_release(int keycode, t_player *player);
void    player_move(t_player *player);

#endif