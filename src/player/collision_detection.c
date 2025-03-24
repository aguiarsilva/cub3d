#include "cub3d.h"


//tuilitites to validate movement

// bool	ft_confirm_valid_pos_wall_collision(t_game_data *game_data, double x, double y)
// {
// 	return (game_data->map[(int)y][(int)x] == '0');
// }

// bool	ft_confirm_valid_pos_in_map(t_game_data *game_data, double x, double y)
// {
// 	if (x < 0.25 || x >= game_data->map_data.map_width - 1.25)
// 		return (false);
// 	if (y < 0.25 || y >= game_data->map_data.map_width -0.25)
// 		return (false);
// 	return (true);
// }

// bool	ft_confirm_valid_pos(t_game_data *game_data, double x, double y)
// {
// 	if (ft_confirm_valid_pos_in_map(game_data, x, y))
// 		return (true);
// 	if (ft_confirm_valid_pos_wall_collision(game_data, x, y))
// 		return (true);
// 	return (false);
// }

// int	ft_validate_movement(t_game_data *game_data, double next_x, double next_y)
// {
// 	int	moved;

// 	moved = 0;
// 	if (ft_confirm_valid_pos(game_data, next_x, game_data->player.y_pos))
// 	{
// 		game_data->player.x_pos = next_x;
// 		moved = 1;
// 	}
// 	if (ft_confirm_valid_pos(game_data, game_data->player.x_pos, next_y))
// 	{
// 		game_data->player.y_pos = next_y;
// 		moved = 1;
// 	}
// 	return (moved);
// }


//validate movement

bool is_valid_wall_position(t_game_data *game_data, double x, double y) {
    return game_data->map[(int)y][(int)x] == '0';
}

bool is_within_map_bounds(t_game_data *game_data, double x, double y) {
    return !(x < 0.25 || x >= game_data->map_data.map_width - 1.25 ||
             y < 0.25 || y >= game_data->map_data.map_height - 0.25);
}

bool is_valid_position(t_game_data *game_data, double x, double y) {
    return is_within_map_bounds(game_data, x, y) && is_valid_wall_position(game_data, x, y);
}

int ft_validate_movement(t_game_data *game_data, double next_x, double next_y) {
    int has_moved = 0;
    if (is_valid_position(game_data, next_x, game_data->player.y_pos)) {
        game_data->player.x_pos = next_x;
        has_moved = 1;
    }
    if (is_valid_position(game_data, game_data->player.x_pos, next_y)) {
        game_data->player.y_pos = next_y;
        has_moved = 1;
    }
    return has_moved;
}



//intialize player direction

// void	ft_init_player_north_south(t_player *player)
// {
// 	if (player->movement.direction == 'S')
// 	{
// 		player->dir_x = 0;
// 		player->dir_y = 1;
// 		player->plane_x = -0.66;
// 		player->plane_y = 0;
// 	}
// 	else if (player->movement.direction == 'N')
// 	{
// 		player->dir_x = 0;
// 		player->dir_y = -1;
// 		player->plane_x = 0.66;
// 		player->plane_y = 0;
// 	}
// 	else
// 		return ;
// }

// void	ft_init_player_east_west(t_player *player)
// {
// 	if (player->movement.direction == 'W')
// 	{
// 		player->dir_x = -1;
// 		player->dir_y = 0;
// 		player->plane_x = 0;
// 		player->plane_y = -0.66;
// 	}
// 	else if (player->movement.direction == 'E')
// 	{
// 		player->dir_x = 1;
// 		player->dir_y = 0;
// 		player->plane_x = 0;
// 		player->plane_y = 0.66;
// 	}
// 	else
// 		return ;
// }

// void	ft_initialize_player_direction(t_game_data *game_data)
// {
// 	ft_init_player_north_south(&game_data->player);
// 	ft_init_player_east_west(&game_data->player);
// }

