#include "cub3d.h"

// int ft_build_map(t_game_data *game_data, char **file, int i)
// {
// 	int index_value, j;

// 	// Count map lines
// 	index_value = i;
// 	while (file[i])
// 	{
// 		j = 0;
// 		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r' || file[i][j] == '\v' || file[i][j] == '\f')
// 			j++;
// 		if (file[i][j] != '1')
// 			break;
// 		i++;
// 	}
// 	game_data->map_data.end_found = i;
// 	game_data->map_data.map_height = i - index_value;

// 	// Allocate and fill map
// 	game_data->map_data.map_width = ft_max_width(&game_data->map_data, index_value);
// 	game_data->map = malloc(sizeof(char *) * (game_data->map_data.map_height + 1));
// 	if (!game_data->map)
// 		return (ft_error_msg(NULL, ERR_MALLOC, STATUS_FAIL));

// 	for (int row = 0, idx = index_value; row < game_data->map_data.map_height; row++, idx++)
// 	{
// 		j = 0;
// 		game_data->map[row] = malloc(sizeof(char) * (game_data->map_data.map_width + 1));
// 		if (!game_data->map[row])
// 			return (ft_error_msg(NULL, ERR_MALLOC, STATUS_FAIL));
// 		while (file[idx][j] && file[idx][j] != '\n')
// 			game_data->map[row][j] = file[idx][j], j++;
// 		while (j < game_data->map_data.map_width)
// 			game_data->map[row][j++] = '\0';
// 	}
// 	game_data->map[game_data->map_data.map_height] = NULL;

// 	// Convert spaces into walls
// 	for (int row = 0; game_data->map[row]; row++)
// 	{
// 		j = 0;
// 		while (game_data->map[row][j] == ' ' || game_data->map[row][j] == '\t' || game_data->map[row][j] == '\r' || game_data->map[row][j] == '\v' || game_data->map[row][j] == '\f')
// 			j++;
// 		while (game_data->map[row][++j])
// 		{
// 			if (game_data->map[row][j] == ' ' && j != game_data->map[row][ft_strlen(game_data->map[row]) - 1])
// 				game_data->map[row][j] = '1';
// 		}
// 	}
// 	return (STATUS_OK);
// }


int	ft_record_lines(t_game_data *game_data, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	game_data->map_data.end_found = i;
	return (i - index_value);
}

int	ft_fill_map_table(t_map_data *map_data, char **map_table, int index)
{
	int		i;
	int		j;

	map_data->map_width = ft_max_width(map_data, index);
	i = 0;
	while (i < map_data->map_height)
	{
		j = 0;
		map_table[i] = malloc(sizeof(char) * (map_data->map_width + 1));
		if (!map_table[i])
			return (ft_error_msg(NULL, ERR_MALLOC, STATUS_FAIL));
		while (map_data->file[index][j] && map_data->file[index][j] != '\n')
		{
			map_table[i][j] = map_data->file[index][j];
			j++;
		}	
		while (j < map_data->map_width)
			map_table[i][j++] = '\0';
		i++;
		index++;
	}
	map_table[i] = NULL;
	return (STATUS_OK);
}

int	ft_get_map_data(t_game_data *game_data, char **file, int i)
{
	game_data->map_data.map_height = ft_record_lines(game_data, file, i);
	game_data->map = malloc(sizeof(char *) * (game_data->map_data.map_height + 1));
	if (!game_data->map)
		return (ft_error_msg(NULL, ERR_MALLOC, STATUS_FAIL));
	if (ft_fill_map_table(&game_data->map_data, game_data->map, i) == STATUS_FAIL)
		return (STATUS_FAIL);
	return (STATUS_OK);
}

void	ft_convert_space_to_wall(t_game_data *game_data)
{
	int	i;
	int	j;

	i = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j] == ' ' || game_data->map[i][j] == '\t'
		|| game_data->map[i][j] == '\r'
		|| game_data->map[i][j] == '\v' || game_data->map[i][j] == '\f')
			j++;
		while (game_data->map[i][++j])
		{
			if (game_data->map[i][j] == ' '
				&& j != game_data->map[i][ft_strlen(game_data->map[i]) - 1])
				game_data->map[i][j] = '1';
		}
		i++;
	}
}

int	ft_build_map(t_game_data *game_data, char **file, int i)
{
	if (ft_get_map_data(game_data, file, i) == STATUS_FAIL)
		return (STATUS_FAIL);
	ft_convert_space_to_wall(game_data);
	return (STATUS_OK);
}