#include "cub3d.h"

int ft_build_map(t_game_data *game_data, char **file, int i)
{
	int index_value, j;

	// Count map lines
	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r' || file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break;
		i++;
	}
	game_data->map_data.end_found = i;
	game_data->map_data.map_height = i - index_value;

	// Allocate and fill map
	game_data->map_data.map_width = ft_find_biggest_len(&game_data->map_data, index_value);
	game_data->map = malloc(sizeof(char *) * (game_data->map_data.map_height + 1));
	if (!game_data->map)
		return (ft_error_msg(NULL, ERR_MALLOC, STATUS_FAIL));

	for (int row = 0, idx = index_value; row < game_data->map_data.map_height; row++, idx++)
	{
		j = 0;
		game_data->map[row] = malloc(sizeof(char) * (game_data->map_data.map_width + 1));
		if (!game_data->map[row])
			return (ft_error_msg(NULL, ERR_MALLOC, STATUS_FAIL));
		while (file[idx][j] && file[idx][j] != '\n')
			game_data->map[row][j] = file[idx][j], j++;
		while (j < game_data->map_data.map_width)
			game_data->map[row][j++] = '\0';
	}
	game_data->map[game_data->map_data.map_height] = NULL;

	// Convert spaces into walls
	for (int row = 0; game_data->map[row]; row++)
	{
		j = 0;
		while (game_data->map[row][j] == ' ' || game_data->map[row][j] == '\t' || game_data->map[row][j] == '\r' || game_data->map[row][j] == '\v' || game_data->map[row][j] == '\f')
			j++;
		while (game_data->map[row][++j])
		{
			if (game_data->map[row][j] == ' ' && j != game_data->map[row][ft_strlen(game_data->map[row]) - 1])
				game_data->map[row][j] = '1';
		}
	}
	return (STATUS_OK);
}
