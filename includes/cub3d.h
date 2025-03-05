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

// Movement and rotation speeds
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.05

// // Color definitions (optional) move to colour tools
// # define BLACK 0x000000
// # define WHITE 0xFFFFFF


typedef struct s_img_data
{
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		*addr;
	void	*img;
}	t_img_data;

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
    int		floor_color;
    int		ceiling_color;
    int		config_found;  // Bitwise flag to track found elements
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
    unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	double			step;
	double			pos;
    t_config        texture_config;
}	t_texture_data;

// Player structure
typedef struct s_player {
    double	x_pos;
    double	y_pos;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
}	t_player;

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
	t_map_data	    mapinfo;
	t_img_data		minimap;
}	          t_game_data;

// Function prototypes
int ft_error_msg(char *arg, char *str, int code);

#endif