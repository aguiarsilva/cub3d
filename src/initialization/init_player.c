#include "cub3d.h"

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

//intitialize player movement
void	ft_initialize_movemement_direction(t_player *player)
{
	switch (player->movement.direction)
	{
		case 'N':
			player->dir_x = 0;
			player->dir_y = -1;
			player->plane_x = 0.66;
			player->plane_y = 0;
			break;
		case 'S':
			player->dir_x = 0;
			player->dir_y = 1;
			player->plane_x = -0.66;
			player->plane_y = 0;
			break;
		case 'E':
			player->dir_x = 1;
			player->dir_y = 0;
			player->plane_x = 0;
			player->plane_y = 0.66;
			break;
		case 'W':
			player->dir_x = -1;
			player->dir_y = 0;
			player->plane_x = 0;
			player->plane_y = -0.66;
			break;
		default:
			break;
	}
}


void	ft_initialize_player_direction(t_game_data *game_data)
{
	ft_initialize_movemement_direction(&game_data->player);
}
