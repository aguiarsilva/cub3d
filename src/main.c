
#include "../includes/cub3d.h"

char    **get_map(void)
{
    char    **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000000000001";
    map[4] = "100000000000001";
    map[5] = "100000000000001";
    map[6] = "100000000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void game_init(t_game *game)
{
    player_init(&game->player);
    game->map = get_map();
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->line_size, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

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

void    draw_map(t_game *game)
{
    char    **map = game->map;
    int     color = 0x0000FF;

    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '1')
                make_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void    clear_image(t_game *game)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
}

bool    touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK:

    if (game->map[y][x] == '1')
        return true;
    return false;
}

int draw_loop(t_game *game)
{
    t_player    *player = &game->player;
    player_move(player);
    clear_image(game);
    make_square(player->x, player->y, 10, 0xFF0000, game);
    draw_map(game);
    
    float fraction = PI / 3 / WIDTH;
    float start_x = player_angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        draw
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

int main(void)
{
    t_game  game;

    game_init(&game);
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    //make_square(WIDTH / 2, HEIGHT / 2, 10, 0xFF0000, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);

    return 0;
}