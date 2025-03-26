#include "cub3d.h"

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
	int	row;
	int	col;

	row = 0;
	game_data->player.movement.direction = '0';
	while (map_table[row] != NULL)
	{
		col = 0;
		while (map_table[row][col])
		{
			ft_skip_whitespace(map_table[row], &col);
			if (ft_validate_map_char(game_data, map_table[row][col])
				== STATUS_FAIL)
				return (STATUS_FAIL);
			if (ft_handle_player_direction(game_data, map_table[row][col])
				== STATUS_FAIL)
				return (STATUS_FAIL);
			col++;
		}
		row++;
	}
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
		return (ft_error_msg(game_data->map_data.path,
				ERR_MAP_MISSING, STATUS_FAIL));
	if (ft_validate_map_boundaries(&game_data->map_data, map_table)
		== STATUS_FAIL)
		return (ft_error_msg(game_data->map_data.path,
				ERR_MAP_NO_WALLS, STATUS_FAIL));
	if (game_data->map_data.map_height < 3)
		return (ft_error_msg(game_data->map_data.path,
				ERR_MAP_TOO_SMALL, STATUS_FAIL));
	if (ft_validate_map_components(game_data, map_table) == STATUS_FAIL)
		return (STATUS_FAIL);
	if (ft_validate_player_position(game_data, map_table) == STATUS_FAIL)
		return (STATUS_FAIL);
	if (ft_validate_map_end_reached(&game_data->map_data) == STATUS_FAIL)
		return (ft_error_msg(game_data->map_data.path, ERR_MAP_LAST,
				STATUS_FAIL));
	return (STATUS_OK);
}
