#include "cub3d.h"


static int *ft_parse_rgb_values(char *line)
{
	char **rgb_to_convert;
	int *rgb;
	int i, count;

	rgb_to_convert = ft_split(line, ',');
	if (!rgb_to_convert)
		return (NULL);

	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		ft_free_table((void **)rgb_to_convert);
		return (NULL);
	}

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		ft_error_msg(NULL, ERR_MALLOC, 0);
		ft_free_table((void **)rgb_to_convert);
		return (NULL);
	}

	for (i = 0; i < 3; i++)
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || !ft_str_isdigit(rgb_to_convert[i]))
		{
			ft_free_table((void **)rgb_to_convert);
			free(rgb);
			return (NULL);
		}
	}
	ft_free_table((void **)rgb_to_convert);
	return (rgb);
}

int ft_fill_color_textures(t_game_data *game_data, t_texture_data *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (ft_error_msg(game_data->map_data.path, ERR_FLOOR_CEILING, STATUS_ERROR));
	if (!textures->hex_ceiling && line[j] == 'C')
	{
		textures->hex_ceiling = ft_parse_rgb_values(line + j + 1);
		if (!textures->hex_ceiling)
			return (ft_error_msg(game_data->map_data.path, ERR_COLOR_CEILING, STATUS_ERROR));
	}
	else if (!textures->hex_floor && line[j] == 'F')
	{
		textures->hex_floor = ft_parse_rgb_values(line + j + 1);
		if (!textures->hex_floor)
			return (ft_error_msg(game_data->map_data.path, ERR_COLOR_FLOOR, STATUS_ERROR));
	}
	else
		return (ft_error_msg(game_data->map_data.path, ERR_FLOOR_CEILING, STATUS_ERROR));
	return (STATUS_OK);
}
