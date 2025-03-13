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
    if (textures->texture_config.no_texture_path)
		free(textures->texture_config.no_texture_path);
	if (textures->texture_config.so_texture_path)
		free(textures->texture_config.so_texture_path);
	if (textures->texture_config.we_texture_path)
		free(textures->texture_config.we_texture_path);
	if (textures->texture_config.ea_texture_path)
		free(textures->texture_config.ea_texture_path);
	if (textures->texture_config.floor_color)
		free(textures->texture_config.floor_color);
	if (textures->texture_config.ceiling_color)
		free(textures->texture_config.ceiling_color);
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