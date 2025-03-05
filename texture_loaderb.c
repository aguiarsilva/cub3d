#include "cub3d.h"

static int load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, 
                                        &texture->width, &texture->height);
    if (!texture->img)
        return (0);
        
    texture->data = (int *)mlx_get_data_addr(texture->img, 
                                            &texture->bits_per_pixel,
                                            &texture->line_length,
                                            &texture->endian);
    if (!texture->data)
    {
        mlx_destroy_image(game->mlx, texture->img);
        return (0);
    }
    return (1);
}

int load_textures(t_game *game)
{
    if (!load_texture(game, &game->north_tex, game->config.no_texture_path) ||
        !load_texture(game, &game->south_tex, game->config.so_texture_path) ||
        !load_texture(game, &game->east_tex, game->config.we_texture_path) ||
        !load_texture(game, &game->west_tex, game->config.ea_texture_path))
    {
        ft_putendl_fd("Error\nFailed to load textures", 2);
        return (0);
    }
    return (1);
}