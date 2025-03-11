#include "cub3d.h"


// need to refactor and convert to while loop also need to fix norm errors


int ft_validate_map(t_game_data *game_data, char **map_table)
{
    int i, j;

    // Check if the map is missing
    if (!game_data->map)
        return ft_error_msg(game_data->map_data.path, ERR_MAP_MISSING, STATUS_FAIL);

    // Check top and bottom borders
    for (i = 0; map_table[i]; i++)
    {
        for (j = 0; map_table[i][j]; j++)
        {
            if (i == 0 || i == game_data->map_data.map_height - 1)
            {
                if (map_table[i][j] != '1' && map_table[i][j] != ' ' && map_table[i][j] != '\t' && map_table[i][j] != '\r' && map_table[i][j] != '\v' && map_table[i][j] != '\f')
                    return ft_error_msg(game_data->map_data.path, ERR_MAP_NO_WALLS, STATUS_FAIL);
            }
        }
    }

    // Check side borders
    for (i = 1; i < game_data->map_data.map_height - 1; i++)
    {
        if (map_table[i][0] != '1' || map_table[i][ft_strlen(map_table[i]) - 1] != '1')
            return ft_error_msg(game_data->map_data.path, ERR_MAP_NO_WALLS, STATUS_FAIL);
    }

    // Check map height
    if (game_data->map_data.map_height < 3)
        return ft_error_msg(game_data->map_data.path, ERR_MAP_TOO_SMALL, STATUS_FAIL);

    // Check map elements and player position
    game_data->player.movement.direction = '0';
    for (i = 0; map_table[i]; i++)
    {
        for (j = 0; map_table[i][j]; j++)
        {
            if (ft_strchr("10NSEW", map_table[i][j]) == NULL)
                return ft_error_msg(game_data->map_data.path, ERR_INV_LETTER, STATUS_FAIL);

            if (ft_strchr("NSEW", map_table[i][j]))
            {
                if (game_data->player.movement.direction != '0')
                    return ft_error_msg(game_data->map_data.path, ERR_NUM_PLAYER, STATUS_FAIL);
                game_data->player.movement.direction = map_table[i][j];
                game_data->player.x_pos = (double)j + 0.5;
                game_data->player.y_pos = (double)i + 0.5;
                map_table[i][j] = '0';
            }
        }
    }

    // Check player position validity
    i = (int)game_data->player.y_pos;
    j = (int)game_data->player.x_pos;
    if (ft_strlen(map_table[i - 1]) < (size_t)j || ft_strlen(map_table[i + 1]) < (size_t)j ||
        ft_confirm_white_space(map_table[i][j - 1]) == STATUS_OK || ft_confirm_white_space(map_table[i][j + 1]) == STATUS_OK ||
        ft_confirm_white_space(map_table[i - 1][j]) == STATUS_OK || ft_confirm_white_space(map_table[i + 1][j]) == STATUS_OK)
        return ft_error_msg(game_data->map_data.path, ERR_PLAYER_POS, STATUS_FAIL);

    // Check for map end
    for (i = game_data->map_data.end_found; map_table[i]; i++)
    {
        for (j = 0; map_table[i][j]; j++)
        {
            if (map_table[i][j] != ' ' && map_table[i][j] != '\t' && map_table[i][j] != '\r' && map_table[i][j] != '\n' && map_table[i][j] != '\v' && map_table[i][j] != '\f')
                return ft_error_msg(game_data->map_data.path, ERR_MAP_LAST, STATUS_FAIL);
        }
    }

    return STATUS_OK;
}

// validate texture function


int	ft_validate_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_error_val(rgb[i], ERR_TEX_RGB_VAL, STATUS_FAIL));
		i++;
	}
	return (STATUS_OK);
}

unsigned long	ft_convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	ft_validate_textures_map(t_game_data *game_data, t_texture_data *textures)
{
	if (!textures->texture_config.no_texture_path || !textures->texture_config.so_texture_path || !textures->texture_config.we_texture_path
		|| !textures->texture_config.ea_texture_path)
		return (ft_error_msg(game_data->map_data.path, ERR_TEX_MISSING, STATUS_FAIL));
	if (!textures->texture_config.floor_color || !textures->texture_config.ceiling_color)
		return (ft_error_msg(game_data->map_data.path, ERR_COLOR_MISSING, STATUS_FAIL));
	if (ft_file_checker(textures->texture_config.no_texture_path, false) == STATUS_FAIL
		|| ft_file_checker(textures->texture_config.so_texture_path, false) == STATUS_FAIL
		|| ft_file_checker(textures->texture_config.we_texture_path, false) == STATUS_FAIL
		|| ft_file_checker(textures->texture_config.ea_texture_path, false) == STATUS_FAIL
		|| ft_validate_rgb(textures->texture_config.floor_color) == STATUS_FAIL
		|| ft_validate_rgb(textures->texture_config.ceiling_color) == STATUS_FAIL)
		return (STATUS_FAIL);
	textures->hex_floor = ft_convert_rgb_to_hex(textures->texture_config.floor_color);
	textures->hex_ceiling = ft_convert_rgb_to_hex(textures->texture_config.ceiling_color);
	return (STATUS_OK);
}