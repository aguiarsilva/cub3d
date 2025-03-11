#include "cub3d.h"

void free_map(char **map)
{
	int i= 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int get_map_height(char **map)
{
	int count = 0;
	while (map[count])
		count++;
	return count;
}

int get_map_width(char **map)
{
	int max_width = 0;
	int i = 0;
	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return max_width;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_error_msg(NULL, "Usage: ./test_check_file <map.cub>", 1);
		return (1);
	}
	char	*file_path = argv[1];
	//Validate file extension test
	if (!validate_file_extension(file_path))
		return (1);
	//Open and read file (using just a placeholder)
	char **map = read_map_from_file(file_path);
	if (!map)
	{
		ft_error_msg(NULL, "Failed to read the map file", 1);
		return (1);
	}
	//find player position
	int player_x, player_y;
	if (!find_player_pos(map, get_map_height(map), &player_x, &player_y))
	{
		ft_error_msg(NULL, "Invalid player position", 1);
		free_map(map);
		return (1);
	}
	//validate walls
	if (!validate_walls(map, get_map_height(map), get_map_width(map), player_x, player_y))
	{
		ft_error_msg(NULL, "Map walls are not properly closed", 1);
		free_map(map);
		return (1);
	}

	printf(GREEN "Map validation successful!\n" RESET);
	free_map(map);
	return (0);
}
