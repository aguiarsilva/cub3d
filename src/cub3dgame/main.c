/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamuel <dsamuel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:33:07 by dsamuel           #+#    #+#             */
/*   Updated: 2025/03/10 16:59:22 by dsamuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// initialization functions

void	init_ray(t_ray *ray)
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

void	ft_initialize_player(t_player *player)
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

void	ft_initialize_data(t_game_data *game_data)
{
	game_data->mlx = NULL;
	game_data->win = NULL;
	game_data->win_height = SCREEN_HEIGHT;
	game_data->win_width = SCREEN_WIDTH;
	game_data->map = NULL;
	// game_data->texture_pixels = NULL;
	// game_data->textures = NULL;
	ft_initialize_player(&game_data->player);
    ft_initialize_map_data(&game_data->map_data);
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

//move to utils files in utils/utils.c
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


int ft_parse_arguments(t_game_data *game_data, char **argv)
{
    if (ft_file_checker(argv[1], true) == STATUS_FAIL)
        ft_clean_and_quit(game_data, STATUS_FAIL);
    
    
}


int main(int argc, char **argv)
{
    t_game_data game_data;
    
    (void)argv;
    if (argc != 2)
        return (ft_error_msg(NULL, ERR_USAGE, 1));

    ft_initialize_data(&game_data);
    // parse input argument implementation here
    if (ft_parse_arguments(&game_data, argv) != 0)
        return (1);

    // Initialize game data and start the game loop here
    ft_initialize_mlx_screen(&game_data);
    mlx_loop_hook(game_data.mlx, render, &game_data);
    mlx_loop(game_data.mlx);
    // ...
    mlx_loop(game_data.mlx);
	return (0);
    
}