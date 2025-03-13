#include "cub3d.h"


int	ft_empty_char(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (STATUS_FAIL);
	else
		return (STATUS_OK);
}

size_t	ft_max_width(t_map_data *map_data, int i)
{
	size_t	max_len;

	max_len = ft_strlen(map_data->file[i]);
	while (map_data->file[i])
	{
		if (ft_strlen(map_data->file[i]) > max_len)
			max_len = ft_strlen(map_data->file[i]);
		i++;
	}
	return (max_len);
}


bool	ft_comfirm_digit_absence(char *str)
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

int	*ft_move_to_rgb_contents(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || ft_comfirm_digit_absence(rgb_to_convert[i]) == true)
		{
			ft_free_table((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	ft_free_table((void **)rgb_to_convert);
	return (rgb);
}

int	*ft_compose_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		ft_free_table((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		ft_error_msg(NULL, ERR_MALLOC, 0);
		return (0);
	}
	return (ft_move_to_rgb_contents(rgb_to_convert, rgb));
}

int	ft_fill_rgb_color(t_game_data *game_data, t_texture_data *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (ft_error_msg(game_data->map_data.path, ERR_FLOOR_CEILING, STATUS_ERROR));
	if (!textures->texture_config.ceiling_color && line[j] == 'C')
	{
		textures->texture_config.ceiling_color = ft_compose_rgb_colors(line + j + 1);
		if (textures->texture_config.ceiling_color == 0)
			return (ft_error_msg(game_data->map_data.path, ERR_COLOR_CEILING, STATUS_ERROR));
	}
	else if (!textures->texture_config.floor_color && line[j] == 'F')
	{
		textures->texture_config.floor_color = ft_compose_rgb_colors(line + j + 1);
		if (textures->texture_config.floor_color == 0)
			return (ft_error_msg(game_data->map_data.path, ERR_COLOR_FLOOR, STATUS_ERROR));
	}
	else
		return (ft_error_msg(game_data->map_data.path, ERR_FLOOR_CEILING, STATUS_ERROR));
	return (STATUS_OK);
}

