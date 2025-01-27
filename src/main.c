
#include "../includes/cub3d.h"

void game_init(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 1280, 720, "Cub3d");
    game->img = mlx_new_image(game->mlx, 1280, 720);
}

int main(void)
{
    t_game  game;

    game_init(&game);

    mlx_loop(game.mlx);

    return 0;
}