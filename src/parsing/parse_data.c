#include "cub3d.h"

// void ft_parse_data(char *path, t_game_data *game_data)
// {
//     int fd;
//     char *line;
//     int row = 0;
//     int column = 0;
//     int i = 0;
//     int line_count = 0;

//     // Get the number of lines in the file
//     fd = open(path, O_RDONLY);
//     if (fd < 0)
//     {
//         ft_error_msg(path, strerror(errno), errno);
//         return;
//     }
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         line_count++;
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);

//     // Allocate memory for the map file
//     game_data->map_data.line_count = line_count;
//     game_data->map_data.path = path;
//     game_data->map_data.file = ft_calloc(line_count + 1, sizeof(char *));
//     if (!(game_data->map_data.file))
//     {
//         ft_error_msg(NULL, ERR_MALLOC, 0);
//         return;
//     }

//     // Open the file again to fill the map table
//     game_data->map_data.fd = open(path, O_RDONLY);
//     if (game_data->map_data.fd < 0)
//     {
//         ft_error_msg(path, strerror(errno), STATUS_FAIL);
//         return;
//     }
//     line = get_next_line(game_data->map_data.fd);
//     while (line != NULL)
//     {
//         game_data->map_data.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
//         if (!game_data->map_data.file[row])
//         {
//             ft_error_msg(NULL, ERR_MALLOC, 0);
//             ft_free_table((void **)game_data->map_data.file);
//             return;
//         }
//         while (line[i] != '\0')
//         game_data->map_data.file[row][column++] = line[i++];
//         game_data->map_data.file[row++][column] = '\0';
//         column = 0;
//         i = 0;
//         free(line);
//         line = get_next_line(game_data->map_data.fd);
//     }
//     game_data->map_data.file[row] = NULL;
//     close(game_data->map_data.fd);
// }


int	ft_get_total_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error_msg(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	ft_fill_table(int row, int column, int i, t_game_data *game_data)
{
	char	*line;

	line = get_next_line(game_data->map_data.fd);
	while (line != NULL)
	{
		game_data->map_data.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game_data->map_data.file[row])
		{
			ft_error_msg(NULL, ERR_MALLOC, 0);
			return (ft_free_table((void **)game_data->map_data.file));
		}
		while (line[i] != '\0')
			game_data->map_data.file[row][column++] = line[i++];
		game_data->map_data.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game_data->map_data.fd);
	}
	game_data->map_data.file[row] = NULL;
}

void	ft_parse_game_data(char *path, t_game_data *game_data)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	game_data->map_data.line_count = ft_get_total_lines(path);
	game_data->map_data.path = path;
	game_data->map_data.file = ft_calloc(game_data->map_data.line_count \
			+ 1, sizeof(char *));
	if (!(game_data->map_data.file))
	{
		ft_error_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
	game_data->map_data.fd = open(path, O_RDONLY);
	if (game_data->map_data.fd < 0)
		ft_error_msg(path, strerror(errno), STATUS_FAIL);
	else
	{
		ft_fill_table(row, column, i, game_data);
		close(game_data->map_data.fd);
	}
}
