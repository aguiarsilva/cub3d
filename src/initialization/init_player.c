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