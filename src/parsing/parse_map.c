int	read_map_line(int fd, char **line)
{
    char	*temp;

    temp = get_next_line(fd);
    if (!temp)
        return (0);
    *line = ft_strtrim(temp, " \n");
    free(temp);
    if (!(*line) || *line[0] == '\0')
    {
        free(*line);
        *line = NULL;
        return (0);
    }
    return (1);
}

void	sanitize_map_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	process_config_map_or_map(t_game *game, char *line, int *in_map)
{
	if (!(*in_map))
	{
		if (handle_config_line(game, line))
			return (1);
		if (ft_strchr(line, '1') || ft_strchr(line, '0'))
			*in_map = 1;
	}
	if (*in_map)
		store_map_line(game, line);
	return (1);
}

int	validate_map_after_parsing(t_game *game)
{
	if (!validate_config(game) || !validate_map_content(game->map, game->map_height))
	{
		ft_error_msg(NULL, ERR_INV_MAP, 2);
		return (0);
	}
	init_player(game);
	return (1);
}

int	parse_map(t_game *game, char *file_path)
{
	int	fd;
	char	*line;
	int	in_map;
	int	status;

	if (!validate_file_extension(file_path))
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	in_map = 0;
	status = 1;
	while (status && read_map_line(fd, &line))
	{
		sanitize_map_line(line);
		status = process_config_or_map(game, line, &in_map);
		free(line);
	}
	close(fd);
	return validate_map_after_parsing(game);
}

