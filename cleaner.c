#include "cub3d.h"

void cleanup_game(t_game *game)
{
    // Free textures
    if (game->north_tex.img)
        mlx_destroy_image(game->mlx, game->north_tex.img);
    if (game->south_tex.img)
        mlx_destroy_image(game->mlx, game->south_tex.img);
    if (game->east_tex.img)
        mlx_destroy_image(game->mlx, game->east_tex.img);
    if (game->west_tex.img)
        mlx_destroy_image(game->mlx, game->west_tex.img);
        
    // Free config paths
    free(game->config.no_texture_path);
    free(game->config.so_texture_path);
    free(game->config.we_texture_path);
    free(game->config.ea_texture_path);
    
    // Free map
    if (game->map)
    {
        int i = 0;
        while (i < game->map_height)
            free(game->map[i++]);
        free(game->map);
    }
    
    // Cleanup MLX
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        free(game->mlx);
}