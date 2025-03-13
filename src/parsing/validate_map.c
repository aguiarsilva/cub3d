#include "cub3d.h"


// need to refactor and convert to while loop also need to fix norm errors


// int ft_validate_map(t_game_data *game_data, char **map_table)
// {
//     int i, j;

//     // Check if the map is missing
//     if (!game_data->map)
//         return ft_error_msg(game_data->map_data.path, ERR_MAP_MISSING, STATUS_FAIL);

//     // Check top and bottom borders
//     for (i = 0; map_table[i]; i++)
//     {
//         for (j = 0; map_table[i][j]; j++)
//         {
//             if (i == 0 || i == game_data->map_data.map_height - 1)
//             {
//                 if (map_table[i][j] != '1' && map_table[i][j] != ' ' && map_table[i][j] != '\t' && map_table[i][j] != '\r' && map_table[i][j] != '\v' && map_table[i][j] != '\f')
//                     return ft_error_msg(game_data->map_data.path, ERR_MAP_NO_WALLS, STATUS_FAIL);
//             }
//         }
//     }

//     // Check side borders
//     for (i = 1; i < game_data->map_data.map_height - 1; i++)
//     {
//         if (map_table[i][0] != '1' || map_table[i][ft_strlen(map_table[i]) - 1] != '1')
//             return ft_error_msg(game_data->map_data.path, ERR_MAP_NO_WALLS, STATUS_FAIL);
//     }

//     // Check map height
//     if (game_data->map_data.map_height < 3)
//         return ft_error_msg(game_data->map_data.path, ERR_MAP_TOO_SMALL, STATUS_FAIL);

//     // Check map elements and player position
//     game_data->player.movement.direction = '0';
//     for (i = 0; map_table[i]; i++)
//     {
//         for (j = 0; map_table[i][j]; j++)
//         {
//             if (ft_strchr("10NSEW", map_table[i][j]) == NULL)
//                 return ft_error_msg(game_data->map_data.path, ERR_INV_LETTER, STATUS_FAIL);

//             if (ft_strchr("NSEW", map_table[i][j]))
//             {
//                 if (game_data->player.movement.direction != '0')
//                     return ft_error_msg(game_data->map_data.path, ERR_NUM_PLAYER, STATUS_FAIL);
//                 game_data->player.movement.direction = map_table[i][j];
//                 game_data->player.x_pos = (double)j + 0.5;
//                 game_data->player.y_pos = (double)i + 0.5;
//                 map_table[i][j] = '0';
//             }
//         }
//     }

//     // Check player position validity
//     i = (int)game_data->player.y_pos;
//     j = (int)game_data->player.x_pos;
//     if (ft_strlen(map_table[i - 1]) < (size_t)j || ft_strlen(map_table[i + 1]) < (size_t)j ||
//         ft_empty_char(map_table[i][j - 1]) == STATUS_OK || ft_empty_char(map_table[i][j + 1]) == STATUS_OK ||
//         ft_empty_char(map_table[i - 1][j]) == STATUS_OK || ft_empty_char(map_table[i + 1][j]) == STATUS_OK)
//         return ft_error_msg(game_data->map_data.path, ERR_PLAYER_POS, STATUS_FAIL);

//     // Check for map end
//     for (i = game_data->map_data.end_found; map_table[i]; i++)
//     {
//         for (j = 0; map_table[i][j]; j++)
//         {
//             if (map_table[i][j] != ' ' && map_table[i][j] != '\t' && map_table[i][j] != '\r' && map_table[i][j] != '\n' && map_table[i][j] != '\v' && map_table[i][j] != '\f')
//                 return ft_error_msg(game_data->map_data.path, ERR_MAP_LAST, STATUS_FAIL);
//         }
//     }

//     return STATUS_OK;
// }

int	ft_validate_horizontal_boundaries(char **map_table, int i, int j)
{
	if (!map_table || !map_table[i] || !map_table[i][j])
		return (STATUS_FAIL);
	while (map_table[i][j] == ' ' || map_table[i][j] == '\t'
	|| map_table[i][j] == '\r' || map_table[i][j] == '\v'
	|| map_table[i][j] == '\f')
		j++;
	while (map_table[i][j])
	{
		if (map_table[i][j] != '1')
			return (STATUS_FAIL);
		j++;
	}
	return (STATUS_OK);
}

int	ft_validate_map_boundaries(t_map_data *map_data, char **map_table)
{
	int	i;
	int	j;

	if (ft_validate_horizontal_boundaries(map_table, 0, 0) == STATUS_FAIL)
		return (STATUS_OK);
	i = 1;
	while (i < (map_data->map_height - 1))
	{
		j = ft_strlen(map_table[i]) - 1;
		if (map_table[i][j] != '1')
			return (STATUS_FAIL);
		i++;
	}
	if (ft_validate_horizontal_boundaries(map_table, i, 0) == STATUS_FAIL)
		return (STATUS_FAIL);
	return (STATUS_OK);
}


int	ft_validate_map_components(t_game_data *game_data, char **map_table)
{
	int	i;
	int	j;

	i = 0;
	game_data->player.movement.direction = '0';
	while (map_table[i] != NULL)
	{
		j = 0;
		while (map_table[i][j])
		{
			while (game_data->map[i][j] == ' ' || game_data->map[i][j] == '\t'
			|| game_data->map[i][j] == '\r'
			|| game_data->map[i][j] == '\v' || game_data->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_table[i][j])))
				return (ft_error_msg(game_data->map_data.path, ERR_INV_LETTER, STATUS_FAIL));
			if (ft_strchr("NSEW", map_table[i][j]) && game_data->player.movement.direction != '0')
				return (ft_error_msg(game_data->map_data.path, ERR_NUM_PLAYER, STATUS_FAIL));
			if (ft_strchr("NSEW", map_table[i][j]) && game_data->player.movement.direction == '0')
				game_data->player.movement.direction = map_table[i][j];
			j++;
		}
		i++;
	}
	return (STATUS_OK);
}

int	ft_validate_position(t_game_data *game_data, char **map_table)
{
	int	i;
	int	j;

	i = (int)game_data->player.y_pos;
	j = (int)game_data->player.x_pos;
	if (ft_strlen(map_table[i - 1]) < (size_t)j
		|| ft_strlen(map_table[i + 1]) < (size_t)j
		|| ft_empty_char(map_table[i][j - 1]) == STATUS_OK
		|| ft_empty_char(map_table[i][j + 1]) == STATUS_OK
		|| ft_empty_char(map_table[i - 1][j]) == STATUS_OK
		|| ft_empty_char(map_table[i + 1][j]) == STATUS_OK)
		return (STATUS_FAIL);
	return (STATUS_OK);
}

int	ft_validate_player_position(t_game_data *game_data, char **map_table)
{
	int	i;
	int	j;

	if (game_data->player.movement.direction == '0')
		return (ft_error_msg(game_data->map_data.path, ERR_PLAYER_DIR, STATUS_FAIL));
	i = 0;
	while (map_table[i])
	{
		j = 0;
		while (map_table[i][j])
		{
			if (ft_strchr("NSEW", map_table[i][j]))
			{
				game_data->player.x_pos = (double)j + 0.5;
				game_data->player.y_pos = (double)i + 0.5;
				map_table[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (ft_validate_position(game_data, map_table) == STATUS_FAIL)
		return (ft_error_msg(game_data->map_data.path, ERR_PLAYER_POS, STATUS_FAIL));
	return (STATUS_OK);
}

int	ft_validate_map_end_reached(t_map_data *map)
{
	int	i;
	int	j;

	i = map->end_found;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (STATUS_FAIL);
			j++;
		}
		i++;
	}
	return (STATUS_OK);
}

int	ft_validate_map(t_game_data *game_data, char **map_table)
{
	if (!game_data->map)
		return (ft_error_msg(game_data->map_data.path, ERR_MAP_MISSING, STATUS_FAIL));
	if (ft_validate_map_boundaries(&game_data->map_data, map_table) == STATUS_FAIL)
		return (ft_error_msg(game_data->map_data.path, ERR_MAP_NO_WALLS, STATUS_FAIL));
	if (game_data->map_data.map_height < 3)
		return (ft_error_msg(game_data->map_data.path, ERR_MAP_TOO_SMALL, STATUS_FAIL));
	if (ft_validate_map_components(game_data, map_table) == STATUS_FAIL)
		return (STATUS_FAIL);
	if (ft_validate_player_position(game_data, map_table) == STATUS_FAIL)
		return (STATUS_FAIL);
	if (ft_validate_map_end_reached(&game_data->map_data) == STATUS_FAIL)
		return (ft_error_msg(game_data->map_data.path, ERR_MAP_LAST, STATUS_FAIL));
	return (STATUS_OK);
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
	if (ft_file_and_dir_checker(textures->texture_config.no_texture_path, false) == STATUS_FAIL
		|| ft_file_and_dir_checker(textures->texture_config.so_texture_path, false) == STATUS_FAIL
		|| ft_file_and_dir_checker(textures->texture_config.we_texture_path, false) == STATUS_FAIL
		|| ft_file_and_dir_checker(textures->texture_config.ea_texture_path, false) == STATUS_FAIL
		|| ft_validate_rgb(textures->texture_config.floor_color) == STATUS_FAIL
		|| ft_validate_rgb(textures->texture_config.ceiling_color) == STATUS_FAIL)
		return (STATUS_FAIL);
	textures->hex_floor = ft_convert_rgb_to_hex(textures->texture_config.floor_color);
	textures->hex_ceiling = ft_convert_rgb_to_hex(textures->texture_config.ceiling_color);
	return (STATUS_OK);
}