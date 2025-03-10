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


