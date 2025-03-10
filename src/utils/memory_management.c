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

    ft_free_map_table(game_data);
    return (STATUS_FAIL);
}