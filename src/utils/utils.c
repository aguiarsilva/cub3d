#include "cub3d.h"


static bool	ft_str_isdigit(char *str)
{
	int		i;
	bool	found_no_digit;

	i = 0;
	found_no_digit = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			found_no_digit = false;
		i++;
	}
	return (found_no_digit);
}

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
	if (!textures->texture_config.ceiling_color && line[j] == 'C')
	{
		textures->texture_config.ceiling_color = ft_parse_rgb_values(line + j + 1);
		if (!textures->texture_config.ceiling_color)
			return (ft_error_msg(game_data->map_data.path, ERR_COLOR_CEILING, STATUS_ERROR));
	}
	else if (!textures->texture_config.floor_color && line[j] == 'F')
	{
		textures->texture_config.floor_color = ft_parse_rgb_values(line + j + 1);
		if (!textures->texture_config.floor_color)
			return (ft_error_msg(game_data->map_data.path, ERR_COLOR_FLOOR, STATUS_ERROR));
	}
	else
		return (ft_error_msg(game_data->map_data.path, ERR_FLOOR_CEILING, STATUS_ERROR));
	return (STATUS_OK);
}

int	ft_confirm_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (STATUS_FAIL);
	else
		return (STATUS_OK);
}

size_t	ft_find_biggest_len(t_map_data *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}
