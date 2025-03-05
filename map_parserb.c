#include "cub3d.h"

// Function declarations (prototypes)
static int is_valid_map_char(char c);
static int validate_map_content(char **map, int height);
static void init_player(t_game *game);

void ft_free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

// Validates file extension (.cub)
static int validate_file_extension(char *file_path)
{
    size_t len;

    len = ft_strlen(file_path);
    if (len < 4 || ft_strncmp(file_path + len - 4, ".cub", 4) != 0)
    {
        ft_putendl_fd("Error\nInvalid file extension. Must be .cub", 2);
        return (0);
    }
    return (1);
}

// Check if character is valid in map
static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || 
            c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

// Check if position is valid (not out of bounds)
static int is_valid_position(int x, int y, int height, int width)
{
    return (x >= 0 && x < width && y >= 0 && y < height);
}

// Validate map walls (flood fill check)
static int validate_walls(char **map, int height, int width, int x, int y)
{
    // If position is out of bounds or is a wall, it's valid
    if (!is_valid_position(x, y, height, width) || map[y][x] == '1')
        return (1);
    
    // If position is a space, it's invalid (map not enclosed)
    if (map[y][x] == ' ')
        return (0);

    // Mark as visited
    map[y][x] = 'V';

    // Check all adjacent positions
    if (!validate_walls(map, height, width, x + 1, y) ||
        !validate_walls(map, height, width, x - 1, y) ||
        !validate_walls(map, height, width, x, y + 1) ||
        !validate_walls(map, height, width, x, y - 1))
        return (0);

    return (1);
}

// For parse_config.c
static int parse_texture_path(char *line, char **texture_path)
{
    while (*line && *line == ' ')
        line++;
    if (!*line)
        return (0);
    *texture_path = ft_strdup(line);
    return (*texture_path != NULL);
}

static int is_valid_rgb(int r, int g, int b)
{
    return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

static int parse_color(char *line, int *color)
{
    char    **rgb;
    int     r, g, b;
    int     count;

    while (*line && *line == ' ')
        line++;
    rgb = ft_split(line, ',');
    if (!rgb)
        return (0);
    count = 0;
    while (rgb[count])
        count++;
    if (count != 3)
    {
        ft_free_split(rgb);
        return (0);
    }
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    ft_free_split(rgb);
    if (!is_valid_rgb(r, g, b))
        return (0);
    *color = (r << 16) | (g << 8) | b;
    return (1);
}

static int handle_config_line(t_game *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return (parse_texture_path(line + 3, &game->config.no_texture_path));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return (parse_texture_path(line + 3, &game->config.so_texture_path));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return (parse_texture_path(line + 3, &game->config.we_texture_path));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return (parse_texture_path(line + 3, &game->config.ea_texture_path));
    else if (ft_strncmp(line, "F ", 2) == 0)
        return (parse_color(line + 2, &game->config.floor_color));
    else if (ft_strncmp(line, "C ", 2) == 0)
        return (parse_color(line + 2, &game->config.ceiling_color));
    return (0);
}

// Find player starting position
static int find_player_pos(char **map, int height, int *x, int *y)
{
    int i;
    int j;

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
    return (0);
}

// Create a map copy for validation
static char **copy_map(char **map, int height)
{
    char **map_copy;
    int i;

    map_copy = (char **)malloc(sizeof(char *) * (height + 1));
    if (!map_copy)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        map_copy[i] = ft_strdup(map[i]);
        if (!map_copy[i])
        {
            while (--i >= 0)
                free(map_copy[i]);
            free(map_copy);
            return (NULL);
        }
        i++;
    }
    map_copy[height] = NULL;
    return (map_copy);
}

// Initialize player direction and position
static void init_player(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (game->map[y][x])
        {
            if (ft_strchr("NSEW", game->map[y][x]))
            {
                game->player.x_pos = x + 0.5;
                game->player.y_pos = y + 0.5;
                if (game->map[y][x] == 'N')
                {
                    game->player.dir_x = 0;
                    game->player.dir_y = -1;
                }
                else if (game->map[y][x] == 'S')
                {
                    game->player.dir_x = 0;
                    game->player.dir_y = 1;
                }
                else if (game->map[y][x] == 'E')
                {
                    game->player.dir_x = 1;
                    game->player.dir_y = 0;
                }
                else if (game->map[y][x] == 'W')
                {
                    game->player.dir_x = -1;
                    game->player.dir_y = 0;
                }
                return;
            }
            x++;
        }
        y++;
    }
}

// Validate basic map content and walls
static int validate_map_content(char **map, int height)
{
    int i;
    int j;
    int player_count;
    char **map_copy;
    int player_x;
    int player_y;
    int max_width;

    player_count = 0;
    max_width = 0;
    i = -1;
    while (++i < height)
    {
        j = -1;
        while (map[i][++j])
        {
            if (!is_valid_map_char(map[i][j]))
                return (0);
            if (ft_strchr("NSEW", map[i][j]))
                player_count++;
        }
        if (j > max_width)
            max_width = j;
    }
    if (player_count != 1)
        return (0);
    map_copy = copy_map(map, height);
    if (!map_copy)
        return (0);
    if (!find_player_pos(map_copy, height, &player_x, &player_y))
    {
        for (i = 0; map_copy[i]; i++)
            free(map_copy[i]);
        free(map_copy);
        return (0);
    }
    int result = validate_walls(map_copy, height, max_width, player_x, player_y);
    for (i = 0; map_copy[i]; i++)
        free(map_copy[i]);
    free(map_copy);
    return (result);
}

static void store_map_line(t_game *game, char *line)
{
    char    **new_map;
    int     i;

    new_map = malloc(sizeof(char *) * (game->map_height + 2));
    if (!new_map)
        return ;
    i = 0;
    while (i < game->map_height)
    {
        new_map[i] = game->map[i];
        i++;
    }
    new_map[i] = ft_strdup(line);
    new_map[i + 1] = NULL;
    free(game->map);
    game->map = new_map;
    game->map_height++;
}

static int validate_config(t_game *game)
{
    return (game->config.no_texture_path && game->config.so_texture_path &&
            game->config.we_texture_path && game->config.ea_texture_path &&
            game->config.floor_color >= 0 && game->config.ceiling_color >= 0);
}

// Main parse function
int parse_map(t_game *game, char *file_path)
{
    int     fd;
    char    *line;
    int     in_map;
    
    if (!validate_file_extension(file_path))
        return (0);
        
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (0);
    
    in_map = 0;
    while ((line = get_next_line(fd)))
    {
        // Skip empty lines
        if (ft_strlen(line) <= 1 && line[0] == '\n')
        {
            free(line);
            continue;
        }
        
        // Remove newline
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
            
        // If we haven't found the map yet, try to parse config
        if (!in_map)
        {
            if (handle_config_line(game, line))
            {
                free(line);
                continue;
            }
            // If line contains map characters, we've found the map
            if (ft_strchr(line, '1') || ft_strchr(line, '0'))
                in_map = 1;
        }
        
        // Store map line
        if (in_map)
        {
            // Add to map array (you'll need to implement this)
            store_map_line(game, line);
        }
        free(line);
    }
    close(fd);
    
    // Validate everything was found
    if (!validate_config(game) || !validate_map_content(game->map, game->map_height))
    {
        ft_putendl_fd("Error\nInvalid map or configuration", 2);
        return (0);
    }
    
    init_player(game);
    return (1);
}