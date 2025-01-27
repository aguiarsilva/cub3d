
#include "../includes/cub3d.h"

void game_init(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

void put_pixel(int x, int y, int color, t_game *game)
{
    int idx;

    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    idx = y * game->line_size + x * game->bpp / 8;
    game->data[idx] = color & 0xFF;
    game->data[idx + 1] = (color >> 8) & 0xFF;
    game->data[idx + 2] = (color >> 16) & 0xFF;
}

void make_square(int x, int y, int size, int color, t_game *game)
{
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);

}

int main(void)
{
    t_game  game;

    game_init(&game);
    make_square(WIDTH / 2, HEIGHT / 2, 10, 0xFF0000, &game);
    mlx_loop(game.mlx);

    return 0;
}