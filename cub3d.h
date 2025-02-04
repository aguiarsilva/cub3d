#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./libft/inc/libft.h"
# include "./libft/inc/get_next_line.h"
# include "./minilibx-linux/mlx.h"

// Screen dimensions
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// Movement and rotation speeds
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.05

// Color definitions (optional)
# define BLACK 0x000000
# define WHITE 0xFFFFFF

// Texture structure
typedef struct s_texture {
	void	*img;
	char	*path;
	int		width;
	int		height;
	int		*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_config {
    char    *no_texture_path;
    char    *so_texture_path;
    char    *we_texture_path;
    char    *ea_texture_path;
    int     floor_color;
    int     ceiling_color;
    int     config_found;  // Bitwise flag to track found elements
} t_config;

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
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

// Main game structure
typedef struct s_game {
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	north_tex;
	t_texture	south_tex;
	t_texture	east_tex;
	t_texture	west_tex;
	t_config    config;
	t_ray		ray;
}	t_game;

// Function prototypes (will be implemented later)
// Parsing functions
int 	parse_map(t_game *game, char *file_path);
int		validate_map(t_game *game);

// Rendering functions
int		init_mlx(t_game *game);
void	render_frame(t_game *game);
void	raycaster(t_game *game);

// Movement functions
void	move_player(t_game *game, int direction);
void	rotate_player(t_game *game, int direction);

// Utility functions
void	free_game(t_game *game);
void	handle_error(char *error_message);

int 	load_textures(t_game *game);
void 	cleanup_game(t_game *game);

#endif // CUB3D_H