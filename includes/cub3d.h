#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "inc/libft.h"
# include "mlx.h"
# include "color_tools.h"

// Screen dimensions
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// Texture size
# define TEXTURE_SIZE 64

// Movement and rotation speeds
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.05

// Error messages
# define ERR_USAGE "Usage: ./cub3d <path/to/map.cub>"
# define ERR_FILE_NOT_CUB "Error\nInvalid file extension. Must be .cub"
# define ERR_FILE_NOT_XPM "Error: Not an .xpm file"
# define ERR_FILE_IS_DIR "Error: Is a directory"
# define ERR_FLOOR_CEILING "Error: Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Error: Invalid floor RGB color"
# define ERR_COLOR_CEILING "Error: Invalid ceiling RGB color"
# define ERR_INV_MAP "Error\nInvalid map or configuration"
# define ERR_INV_LETTER "Error: Invalid character in map"
# define ERR_NUM_PLAYER "Error\nMultiple player positions found"
# define ERR_TEX_RGB_VAL "Error: Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Error: Missing texture(s)"
# define ERR_TEX_INVALID "Error: Invalid texture(s)"
# define ERR_COLOR_MISSING "Error: Missing color(s)"
# define ERR_MAP_MISSING "Error: Missing map"
# define ERR_MAP_TOO_SMALL "Error: Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Error: Map is not surrounded by walls"
# define ERR_MAP_LAST "Error: Map is not the last element in file"
# define ERR_PLAYER_POS "Error\nNo player position found"
# define ERR_PLAYER_DIR "Error: Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Error: Could not allocate memory"
# define ERR_MLX_START "Error: Could not start mlx"
# define ERR_MLX_WIN "Error: Could not create mlx window"
# define ERR_MLX_IMG "Error: Could not create mlx image"

typedef struct s_img_data
{
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		*addr;
	void	*img;
}	t_img_data;

typedef enum e_status
{
    STATUS_OK = 0,
    STATUS_FAIL = 1,
    STATUS_ERROR = 2,
    STATUS_BREAK = 3,
    STATUS_CONTINUE = 4
}	t_status;

typedef enum e_direction
{
    DIR_NORTH = 0,
    DIR_SOUTH = 1,
    DIR_EAST = 2,
    DIR_WEST = 3
}	t_direction;

typedef struct s_minimap
{
    int		    size;
	int		    offset_x;
	int		    offset_y;
	int		    view_dist;
	int		    tile_size;
	char	    **map;
    t_img_data	*image;
}	t_minimap;

typedef struct s_map_data
{
	int			fd;
	int			line_count;
	int			map_height;
	int			map_width;
	int			end_found;
	char		*path;
	char		**file;
}	t_map_data;


typedef struct s_config {
    int		*floor_color;
    int		*ceiling_color;
    char	*no_texture_path;
    char	*so_texture_path;
    char	*we_texture_path;
    char	*ea_texture_path;
}	t_config;

typedef struct s_texture_data
{
    int				size;
	int				x_dir;
	int				y_dir;
    int             config_found;
    unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	double			step;
	double			pos;
    t_config        texture_config;
}	t_texture_data;

typedef struct s_movement
{
    int     moved;
    int     move_x;
    int     move_y;
    int     rotate;
    char    direction;
}               t_movement;

// Player structure
typedef struct s_player {
    double	x_pos;
    double	y_pos;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
    t_movement movement;
}	            t_player;

// Raycasting data structure
typedef struct s_ray {
    int		map_x;
    int		map_y;
    int		step_x;
    int		step_y;
    int		side;
    int		line_height;
    int		draw_start;
    int		draw_end;
    double	camera_x;
    double	ray_dir_x;
    double	ray_dir_y;
    double	side_dist_x;
    double	side_dist_y;
    double	delta_dist_y;
    double	delta_dist_x;
    double	wall_dist;
}	            t_ray;

typedef struct s_game_data
{
	void		    *mlx;
	void		    *win;
	int			    win_height;
	int			    win_width;
	int			    **texture_pixels;
	int			    **textures;
	char		    **map;
	t_player	    player;
	t_ray		    ray;
	t_texture_data  texture_data;
	t_map_data	    map_data;
	// t_img_data		mini_map;
}	          t_game_data;

// Function prototypes
int ft_error_msg(char *arg, char *str, int code);

int	ft_error_val(int arg, char *str, int er_code);
int	ft_file_and_dir_checker(char *arg, bool cub_file);
int ft_validate_map(t_game_data *game_data, char **map_table);
int ft_validate_textures_map(t_game_data *game_data, t_texture_data *textures);
void ft_parse_game_data(char *path, t_game_data *game_data);
int	ft_get_gamefiles_data(t_game_data *game_data, char **map);
int ft_build_map(t_game_data *game_data, char **file, int i);

// Free Functions
void ft_free_table(void **table);
//free all textures data
void ft_free_texture_data(t_texture_data *textures);
void ft_free_map_table(t_game_data *game_data);
int ft_free_game_data(t_game_data *game_data);

//utils
int	ft_fill_rgb_color(t_game_data *game_data, t_texture_data *textures, char *line, int j);

int	   ft_empty_char(char c);
size_t	ft_max_width(t_map_data *map_data, int i);

#endif
