/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamuel <dsamuel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:33:07 by dsamuel           #+#    #+#             */
/*   Updated: 2025/03/12 18:22:23 by dsamuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//can be refactored and moved to error_handling files

int ft_error_msg(char *arg, char *str, int er_code)
{
    ft_putstr_fd(RED "cub3D: Error", 2);
    if (arg)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(arg, 2);
    }
    if (str)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(str, 2);
    }
    ft_putstr_fd("\n" RESET, 2);
    return er_code;
}

int	ft_error_val(int arg, char *str, int er_code)
{
	ft_putstr_fd(RED "cub3D: Error: ", 2);
	ft_putnbr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n" RESET, 2);
	return (er_code);
}


//move to utils folder under a file
void ft_clean_and_exit(t_game_data *game_data, int exit_code)
{
    if (!game_data)
        exit(exit_code);
    if (game_data->win && game_data->mlx)
        mlx_destroy_window(game_data->mlx, game_data->win);
    if (game_data->mlx)
    {
        mlx_destroy_display(game_data->mlx);
        mlx_loop_end(game_data->mlx);
        free(game_data->mlx);
    }
    ft_free_game_data(game_data);
    exit(exit_code);
}

// int ft_exit_game(t_game_data *game_data)
// {
//     ft_clean_and_exit(game_data, STATUS_OK);
//     return (STATUS_OK);
// }

int ft_exit_game(t_game_data *game_data)
{
    ft_clean_and_exit(game_data, 0);
    return (0);
}


// initialization functions
// need to be refactored and moved to the apprropraite inititalziation folder
//Initilize image data function
void	ft_initialize_img_data(t_img_data *image)
{
	image->img = NULL;
	image->addr = NULL;
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
}

void	ft_initialize_ray_data(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->wall_dist = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	// ray->wall_x = 0;
}

void	ft_initialize_map_data(t_map_data *map_data)
{
	map_data->fd = 0;
	map_data->line_count = 0;
	map_data->path = NULL;
	map_data->file = NULL;
	map_data->map_height = 0;
	map_data->map_width = 0;
	map_data->end_found = 0;
}


//need to be refactored and moved to the appropriate initialization folder
void	ft_initialize_player_data(t_player *player)
{
	player->dir_x = 0.0;
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.0;
    player->x_pos = 0.0;
    player->x_pos = 0.0;
    player->movement.direction = '\0';
    player->movement.moved = 0;
    player->movement.move_x = 0;
    player->movement.move_y = 0;
    player->movement.rotate = 0;
}



//move mlx initaizlization folder files


void	ft_initialize_image(t_game_data *game_data, t_img_data *image, int width, int height)
{
	ft_initialize_img_data(image);
	image->img = mlx_new_image(game_data->mlx, width, height);
	if (image->img == NULL)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MLX_IMG, 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	ft_initialize_texture_img(t_game_data *game_data, t_img_data *image, char *path)
{
	ft_initialize_img_data(image);
	image->img = mlx_xpm_file_to_image(game_data->mlx, path, &game_data->texture_data.size,
			&game_data->texture_data.size);
	if (image->img == NULL)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MLX_IMG, 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}


int	*ft_convert_xpm_to_img(t_game_data *game_data, char *path)
{
	int		x;
	int		y;
    int		*buffer;
	t_img_data	tmp;

	ft_initialize_texture_img(game_data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * game_data->texture_data.size * game_data->texture_data.size);
	if (!buffer)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MALLOC, 1));
	y = 0;
	while (y < game_data->texture_data.size)
	{
		x = 0;
		while (x < game_data->texture_data.size)
		{
			buffer[y * game_data->texture_data.size + x]
				= tmp.addr[y * game_data->texture_data.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(game_data->mlx, tmp.img);
	return (buffer);
}

void	ft_initialize_textures(t_game_data *game_data)
{
	game_data->textures = ft_calloc(5, sizeof * game_data->textures);
	if (!game_data->textures)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MALLOC, 1));
	game_data->textures[DIR_NORTH] = ft_convert_xpm_to_img(game_data, game_data->texture_data.texture_config.no_texture_path);
	game_data->textures[DIR_SOUTH] = ft_convert_xpm_to_img(game_data, game_data->texture_data.texture_config.so_texture_path);
	game_data->textures[DIR_WEST] = ft_convert_xpm_to_img(game_data, game_data->texture_data.texture_config.we_texture_path);
	game_data->textures[DIR_EAST] = ft_convert_xpm_to_img(game_data, game_data->texture_data.texture_config.ea_texture_path);
}


//intialize textures values
void ft_initialize_textures_data(t_texture_data *textures)
{
    textures->texture_config.ceiling_color = 0;
    textures->texture_config.floor_color = 0;
    textures->texture_config.no_texture_path = NULL;
    textures->texture_config.so_texture_path = NULL;
    textures->texture_config.we_texture_path = NULL;
    textures->texture_config.ea_texture_path = NULL;
    textures->hex_floor = 0x0;
    textures->hex_ceiling = 0x0;
    textures->size = TEXTURE_SIZE;
    textures->step = 0.0;
    textures->pos = 0.0;
    textures->x_dir = 0;
    textures->y_dir = 0;
    
}


// need to be refactored and moved to the appropriate initialization folder
void	ft_initialize_data(t_game_data *game_data)
{
	game_data->mlx = NULL;
	game_data->win = NULL;
	game_data->win_height = SCREEN_HEIGHT;
	game_data->win_width = SCREEN_WIDTH;
	game_data->map = NULL;
	game_data->texture_pixels = NULL;
	game_data->textures = NULL;
	ft_initialize_player_data(&game_data->player);
    ft_initialize_map_data(&game_data->map_data);
    ft_initialize_textures_data(&game_data->texture_data);
} 


// initialize screen and handle basic events as describe in this milestone
void ft_initialize_mlx_screen(t_game_data *game_data)
{
    game_data->mlx = mlx_init();
    if (!game_data->mlx)
    {
        // printf("did not work");
        // exit(1);
        // implement clean and exit function
        ft_clean_and_exit(game_data, ft_error_msg("NULL", ERR_MLX_START, 1));
    }
    game_data->win = mlx_new_window(game_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
    if (!game_data->win)
    {
        // printf("window did start");
        // exit(1);
        // implement clean and exit function
        ft_clean_and_exit(game_data, ft_error_msg("NULL", ERR_MLX_WIN, 1));
    }
    // implement more feature here just basic start
}



int render(t_game_data *game_data)
{
    // Clear the window or perform any necessary pre-rendering steps
    mlx_clear_window(game_data->mlx, game_data->win);

    // Render the game scene here
    // ...

    // // Display the rendered frame
    // mlx_put_image_to_window(game_data->mlx, game_data->win, 0, 0);

    return 0;
}



int ft_parse_arguments(t_game_data *game_data, char **argv)
{
    if (ft_file_and_dir_checker(argv[1], true) == STATUS_FAIL)
        ft_clean_and_exit(game_data, STATUS_FAIL);

    //parse map data
    ft_parse_game_data(argv[1], game_data);
    if (ft_get_gamefiles_data(game_data, game_data->map_data.file) == STATUS_FAIL)
        return (ft_free_game_data(game_data));
    if (ft_validate_map(game_data, game_data->map) == STATUS_FAIL)
        return (ft_free_game_data(game_data));
    // get the data from different files both maps and textures
    if (ft_validate_textures_map(game_data, &game_data->texture_data) == STATUS_FAIL)
        return (ft_free_game_data(game_data));

    // initialize player direction ... to be implemented
    
    return (0);
    
}


int main(int argc, char **argv)
{
    t_game_data game_data;
    
    if (argc != 2)
        return (ft_error_msg(NULL, ERR_USAGE, 1));

    ft_initialize_data(&game_data);
    // parse input argument implementation here
    if (ft_parse_arguments(&game_data, argv) != 0)
        return (1);

    // Initialize game data and start the game loop here
    ft_initialize_mlx_screen(&game_data);
    ft_initialize_textures(&game_data);
    
    mlx_loop_hook(game_data.mlx, render, &game_data);
    mlx_loop(game_data.mlx);
    // ...
    mlx_loop(game_data.mlx);
	return (0);
    
}