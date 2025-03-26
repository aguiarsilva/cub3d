#include "cub3d.h"

void ft_free_table(void **table)
{
    size_t i;

    i = 0;
    while (table[i])
    {
        free(table[i]);
        i++;
    }
    if (table)
    {
        free(table);
        table = NULL;
    }
}
//free all textures data
void ft_free_texture_data(t_texture_data *textures)
{
    if (textures->text_config.no_text_path)
		free(textures->text_config.no_text_path);
	if (textures->text_config.so_text_path)
		free(textures->text_config.so_text_path);
	if (textures->text_config.we_text_path)
		free(textures->text_config.we_text_path);
	if (textures->text_config.ea_text_path)
		free(textures->text_config.ea_text_path);
	if (textures->text_config.floor_color)
		free(textures->text_config.floor_color);
	if (textures->text_config.ceiling_color)
		free(textures->text_config.ceiling_color);
}

void ft_free_map_table(t_game_data *game_data)
{
    if (game_data->map_data.fd > 0)
    {
        close(game_data->map_data.fd);
    }
    if (game_data->map_data.file)
    {
        ft_free_table((void **)game_data->map_data.file);
    }
    if (game_data->map)
        ft_free_table((void **)game_data->map);
}

int ft_free_game_data(t_game_data *game_data)
{

    if (game_data->textures)
    {
        ft_free_table((void **)game_data->textures);
    }
    if (game_data->texture_pixels)
    {
        ft_free_table((void **)game_data->texture_pixels);
    }
    ft_free_texture_data(&game_data->texture_data);
    ft_free_map_table(game_data);
    return (STATUS_FAIL);
}

void ft_clean_and_exit(t_game_data *game_data, int exit_code)
{
    if (!game_data)
        exit(exit_code);
    if (game_data->win && game_data->mlx)
        mlx_destroy_window(game_data->mlx, game_data->win);
    if (game_data->mlx)
    {
        mlx_destroy_display(game_data->mlx);
        mlx_loop_end(game_data->mlx);
        free(game_data->mlx);
    }
    ft_free_game_data(game_data);
    exit(exit_code);
}

// int ft_exit_game(t_game_data *game_data)
// {
//     ft_clean_and_exit(game_data, STATUS_OK);
//     return (STATUS_OK);
// }

int ft_exit_game(t_game_data *game_data)
{
    ft_clean_and_exit(game_data, 0);
    return (0);
}