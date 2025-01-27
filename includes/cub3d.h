

#ifndef CUB3D_H
# define CUB3D_H

#define HEIGHT 720
#define WIDTH 1280

#include "../includes/minilibx-linux/mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;

    char    *data;
    int     bpp;
    int     line_size;
    int     endian;
    
}   t_game;

#endif