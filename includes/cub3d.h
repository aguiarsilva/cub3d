/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:27:42 by baguiar-          #+#    #+#             */
/*   Updated: 2025/03/23 13:35:08 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "libft.h"
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

//

// Error messages
# define ERR_USAGE "Usage: ./cub3d <path/to/map.cub>"
# define ERR_FILE_NOT_CUB "Error: The file is not a .cub file"
# define ERR_FILE_NOT_XPM "Error: The texture is not an .xpm file"
# define ERR_FILE_IS_DIR "Error: The specified path is a directory"
# define ERR_FLOOR_CEILING "Error: Invalid RGB color(s) for floor/ceiling"
# define ERR_COLOR_FLOOR "Error: Invalid RGB color for floor"
# define ERR_COLOR_CEILING "Error: Invalid RGB color for ceiling"
# define ERR_INVALID_MAP "Error: The map description is incorrect or incomplete"
# define ERR_INV_LETTER "Error: The map contains an invalid character"
# define ERR_NUM_PLAYER "Error: The map contains more than one player"
# define ERR_TEX_RGB_VAL "Error: RGB value out of range (between 0 and 255)"
# define ERR_TEX_MISSING "Error: One or more textures missing"
# define ERR_TEX_INVALID "Error: One or more textures invalid"
# define ERR_COLOR_MISSING "Error: One or more colors missing"
# define ERR_MAP_MISSING "Error: The map is missing from the file"
# define ERR_MAP_TOO_SMALL "Error: The map must be at least 3 lines high"
# define ERR_MAP_NO_WALLS "Error: The map is not fully enclosed by walls"
# define ERR_MAP_LAST "Error: The map is not the last element in file"
# define ERR_PLAYER_POS "Error: Invalid player starting position"
# define ERR_PLAYER_DIR "Error: Map lacks a player position (N, S, E or W)"
# define ERR_MALLOC "Error: Failed to allocate memory"
# define ERR_MLX_START "Error: Failed to start mlx"
# define ERR_MLX_WIN "Error: Failed to create mlx window"
# define ERR_MLX_IMG "Error: Failed to create mlx image"

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
	int			size;
	int			offset_x;
	int			offset_y;
	int			view_dist;
	int			tile_size;
	char		**map;
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

typedef struct s_config
{
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
	int				config_found;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	double			step;
	double			pos;
	t_config		texture_config;
}	t_texture_data;

typedef struct s_movement
{
	int		moved;
	int		move_x;
	int		move_y;
	int		rotate;
	char	direction;
}	t_movement;

// Player structure
typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_movement	movement;
}	t_player;

// ray float point direction
typedef struct s_ray_fpoint
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_y;
	double	delta_dist_x;
	double	wall_dist;
	double	wall_x; // need to find usage
}	t_ray_fpoint;

// Raycasting data structure
typedef struct s_ray
{
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	t_ray_fpoint	ray_distance;
}	t_ray;

typedef struct s_game_data
{
	void			*mlx;
	void			*win;
	int				win_height;
	int				win_width;
	int				**texture_pixels;
	int				**textures;
	char			**map;
	t_player		player;
	t_ray			ray;
	t_texture_data	texture_data;
	t_map_data		map_data;
	// t_img_data		mini_map;
}	t_game_data;

//init function prototypes
void	ft_initialize_ray_data(t_ray *ray);

// Function prototypes
int		ft_error_msg(char *arg, char *str, int code);

int		ft_error_val(int arg, char *str, int er_code);
int		ft_file_and_dir_checker(char *arg, bool cub_file);
int		ft_validate_map(t_game_data *game_data, char **map_table);
int		ft_validate_textures_map(t_game_data *game_data,
			t_texture_data *textures);
void	ft_parse_game_data(char *path, t_game_data *game_data);
int		ft_get_gamefiles_data(t_game_data *game_data, char **map);
int		ft_build_map(t_game_data *game_data, char **file, int i);

// Free Functions
void	ft_free_table(void **table);
//free all textures data
void	ft_free_texture_data(t_texture_data *textures);
void	ft_free_map_table(t_game_data *game_data);
int		ft_free_game_data(t_game_data *game_data);

void	ft_clean_and_exit(t_game_data *game_data, int exit_code);

//utils
int		ft_fill_rgb_color(t_game_data *game_data,
			t_texture_data *textures, char *line, int j);

void	ft_set_image_pixel(t_img_data *image, int x, int y,
			int color_val);

int		ft_empty_char(char c);
size_t	ft_max_width(t_map_data *map_data, int i);

// Graphi set up
void	ft_initialize_graphic_pixels(t_game_data *game_data);

void	ft_get_graphic_location(t_game_data *game_data, t_ray *ray);
void	ft_update_graphic_pixels(t_game_data *game_data,
			t_texture_data *texture, t_ray *ray, int x);

//movement proptotype
int		ft_move_player(t_game_data *game_data);

//Raycasting
int		ft_raycasting(t_player *player, t_game_data *game_data);

//
//
void	ft_setup_input_listeners(t_game_data *game_data);
int		ft_exit_game(t_game_data *game_data);

//Rotate player
int		ft_rotate_player(t_game_data *game_data,
			double rotation_direction);
int		ft_validate_movement(t_game_data *game_data,
			double next_x, double next_y);

//initialize player direction
void	ft_initialize_player_direction(t_game_data *game_data);

#endif