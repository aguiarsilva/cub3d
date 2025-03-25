/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:55:11 by baguiar-          #+#    #+#             */
/*   Updated: 2025/03/25 12:55:15 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// initialization functions
// need to be refactored and moved to the apprropraite inititalziation folder
//Initilize image data function
void	ft_initialize_img_data(t_img_data *image)
{
	/*
	image->img = NULL;
	image->addr = NULL;
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
	*/
	ft_memset(image, 0, sizeof(t_img_data));
}

void  ft_init_ray_fpoint(t_ray_fpoint *ray_fpoint)
{
	// ray_fpoint->camera_x = 0.0;
	// ray_fpoint->ray_dir_x = 0.0;
	// ray_fpoint->ray_dir_y = 0.0;
	// ray_fpoint->side_dist_x = 0.0;
	// ray_fpoint->side_dist_y = 0.0;
	// ray_fpoint->delta_dist_x = 0.0;
	// ray_fpoint->delta_dist_y = 0.0;
	// ray_fpoint->wall_dist = 0.0;
	// ray_fpoint->wall_x = 0.0;
	if (ray_fpoint)
		ft_memset(ray_fpoint, 0, sizeof(t_ray_fpoint));
}

void	ft_initialize_ray_data(t_ray *ray)
{
	/*
	// ray->camera_x = 0;
	// ray->ray_dir_x = 0;
	// ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	// ray->side_dist_x = 0;
	// ray->side_dist_y = 0;
	// ray->delta_dist_x = 0;
	// ray->delta_dist_y = 0;
	// ray->wall_dist = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	// ray->wall_x = 0;
	ft_init_ray_fpoint(&ray->ray_distance);
	*/
	if (ray)
	{
		ft_memset(ray, 0, sizeof(t_ray));
		ft_init_ray_fpoint(&ray->ray_distance);
	}
}

void	ft_initialize_map_data(t_map_data *map_data)
{
	// map_data->fd = 0;
	// map_data->line_count = 0;
	// map_data->path = NULL;
	// map_data->file = NULL;
	// map_data->map_height = 0;
	// map_data->map_width = 0;
	// map_data->end_found = 0;
	if (map_data)
		ft_memset(map_data, 0, sizeof(t_map_data));
}

// need to be refactored and moved to the appropriate initialization folder
void	ft_initialize_data(t_game_data *game_data)
{
	if (game_data)
	{
		ft_memset(game_data, 0, sizeof(t_game_data));
		// game_data->mlx = NULL;
		// game_data->win = NULL;
		game_data->win_height = SCREEN_HEIGHT;
		game_data->win_width = SCREEN_WIDTH;
		// game_data->map = NULL;
		// game_data->texture_pixels = NULL;
		// game_data->textures = NULL;
		ft_initialize_player_data(&game_data->player);
		ft_initialize_map_data(&game_data->map_data);
		ft_initialize_textures_data(&game_data->texture_data);
	} 
}
	
