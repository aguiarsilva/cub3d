#include "cub3d.h"

// function to validate file extension (.cub)

int	validate_file_extension(char *file_path)
{
	size_t	len;

	len = ft_strlen(file_path);
	if (len < 4 || ft_strncmp(file_path + len - 4, ".cub", 4) != 0)
	{
		ft_error_msg(NULL, ERR_FILE_NOT_CUB, 2);
		return (0);
	}
	return (1);
}

//function to check if character is valid in map
int	is_valid_map_char(char c)
{
	return (ft_strchr("01NSEW ", c) != NULL);
}

// function to validate map walls (flood fill check)
int	validate_walls(char **map, int height, int width, int x, int y)
{
	if (!is_valid_position(x, y, height, width))
		return (0);
	if (map[y][x] == 'V' || map[y][x] == '1')
		return (1);
	if (map[y][x] == ' ')
		return (1);
	//mark spot visited
	map[y][x] = 'V';
	if (!validate_walls(map, height, width, x + 1, y) ||
	    !validate_walls(map, height, width, x - 1, y) ||
	    !validate_walls(map, height, width, x, y + 1) ||
	    !validate_walls(map, height, width, x, y - 1))
	   return (0);
	return(1);
}

// function to validate rgb
int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0
		&& g <= 255 && b >= 0 && b <= 255);
}

//function to validate player position
int	is_valid_position(int x, int y, int height, int width)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

int	check_multiple_players(char **map, int height)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < height)
	{
		if (!map[i])
			return (0);
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				count++;
			if (count > 1)
				return (ft_error_msg(NULL, ERR_NUM_PLAYER, 0));
			j++;
		}
		i++;
	}
	return (count == 1);
}

int	find_player_pos(char **map, int height, int *x, int *y)
{
	int	i;
	int	j;

	if (!map || height <= 0 || !x || !y || !check_multiple_players(map, height))
		return (0);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (ft_error_msg(NULL, ERR_PLAYER_POS, 0));
}

