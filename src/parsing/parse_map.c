#include "cub3d.h"




static char *ft_extract_texture_path(char *line, int *j)
{
	int len, i;
	char *path;

	while (line[*j] && (line[*j] == ' ' || line[*j] == '\t'))
		(*j)++;
	len = *j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - *j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[*j] && (line[*j] != ' ' && line[*j] != '\t' && line[*j] != '\n'))
		path[i++] = line[(*j)++];
	path[i] = '\0';

	while (line[*j] && (line[*j] == ' ' || line[*j] == '\t'))
		(*j)++;
	if (line[*j] && line[*j] != '\n')
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static int ft_process_texture_info(t_texture_data *textures, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		return (STATUS_ERROR);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->texture_config.no_texture_path))
		textures->texture_config.no_texture_path = ft_extract_texture_path(line, &j);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->texture_config.so_texture_path))
		textures->texture_config.so_texture_path = ft_extract_texture_path(line, &j);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->texture_config.we_texture_path))
		textures->texture_config.we_texture_path = ft_extract_texture_path(line, &j);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->texture_config.ea_texture_path))
		textures->texture_config.ea_texture_path = ft_extract_texture_path(line, &j);
	else
		return (STATUS_ERROR);
	return (STATUS_OK);
}

int ft_get_file_data(t_game_data *game_data, char **map)
{
	int i, j;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
				j++;
			if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
			{
				if (map[i][j + 1] && ft_isprint(map[i][j + 1]) && !ft_isdigit(map[i][j]))
				{
					if (ft_process_texture_info(&game_data->texture_data, map[i], j) == STATUS_ERROR)
						return (ft_error_msg(game_data->map_data.path, ERR_TEX_INVALID, STATUS_FAIL));
					break;
				}
				else
				{
					if (ft_fill_color_textures(game_data, &game_data->texture_data, map[i], j) == STATUS_ERROR)
						return (STATUS_FAIL);
					break;
				}
			}
			else if (ft_isdigit(map[i][j]))
			{
				if (ft_build_map(game_data, map, i) == STATUS_FAIL)
					return (ft_error_msg(game_data->map_data.path, ERR_INVALID_MAP, STATUS_FAIL));
				return (STATUS_OK);
			}
			j++;
		}
		i++;
	}
	return (STATUS_OK);
}
