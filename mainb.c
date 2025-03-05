#include "cub3d.h"

static int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
    if (!game->win)
        return (0);
    
    // Initialize map components
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    
    // Initialize config components
    game->config.no_texture_path = NULL;
    game->config.so_texture_path = NULL;
    game->config.we_texture_path = NULL;
    game->config.ea_texture_path = NULL;
    game->config.floor_color = -1;
    game->config.ceiling_color = -1;
    
    return (1);
}

static int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 53)  // ESC key
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	// Add other key handlers here (WASD, arrow keys)
	return (0);
}

static int	game_loop(t_game *game)
{
	// Clear previous frame
	// Calculate new frame
	// Render frame
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        ft_putendl_fd("Error\nUsage: ./cub3d map.cub", 2);
        return (1);
    }
    if (!init_game(&game))
    {
        ft_putendl_fd("Error\nFailed to initialize game", 2);
        return (1);
    }
    if (!parse_map(&game, argv[1]))
    {
        cleanup_game(&game);
        return (1);
    }
    if (!load_textures(&game))
    {
        cleanup_game(&game);
        return (1);
    }
    
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    
    cleanup_game(&game);
    return (0);
}