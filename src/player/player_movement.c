#include <cub3d.h>


// listen to events

int	ft_handle_key_press(int key_code, t_game_data *game_data)
{
	if (key_code == XK_Escape)
        ft_exit_game(game_data);
	if (key_code == XK_Left)
		game_data->player.movement.rotate -= 1;
	if (key_code == XK_Right)
		game_data->player.movement.rotate += 1;
	if (key_code == XK_w)
		game_data->player.movement.move_y = 1;
	if (key_code == XK_a)
		game_data->player.movement.move_x = -1;
	if (key_code == XK_s)
		game_data->player.movement.move_y = -1;
	if (key_code == XK_d)
		game_data->player.movement.move_x = 1;
	return (0);
}

int	ft_handle_key_release(int key_code, t_game_data *game_data)
{
	if (key_code == XK_Escape)
        ft_exit_game(game_data);
	if (key_code == XK_w && game_data->player.movement.move_y == 1)
		game_data->player.movement.move_y = 0;
	if (key_code == XK_s && game_data->player.movement.move_y == -1)
		game_data->player.movement.move_y = 0;
	if (key_code == XK_a && game_data->player.movement.move_x == -1)
		game_data->player.movement.move_x += 1;
	if (key_code == XK_d && game_data->player.movement.move_x == 1)
		game_data->player.movement.move_x -= 1;
	if (key_code == XK_Left && game_data->player.movement.rotate <= 1)
		game_data->player.movement.rotate = 0;
	if (key_code == XK_Right && game_data->player.movement.rotate >= -1)
		game_data->player.movement.rotate = 0;
	return (0);
}

void	ft_adjust_mouse_position(t_game_data *game_data, int x, int y)
{
	if (x > game_data->win_width -20)
	{
		x = 20;
		mlx_mouse_move(game_data->mlx, game_data->win, x, y);
	}
	if (x < 20)
	{
		x = game_data->win_width - 20;
		mlx_mouse_move(game_data->mlx, game_data->win, x, y);
	}
}

int	ft_handle_mouse_motion(int x, int y, t_game_data *game_data)
{
	static int	old_x = SCREEN_WIDTH / 2;

	ft_adjust_mouse_position(game_data, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		game_data->player.movement.moved += ft_rotate_player(game_data, -1);
	else if (x > old_x)
		game_data->player.movement.moved += ft_rotate_player(game_data, 1);
	old_x = x;
	return (0);
}

void	ft_setup_input_listeners(t_game_data *game_data)
{
	mlx_hook(game_data->win, ClientMessage, NoEventMask, ft_exit_game, game_data);
	mlx_hook(game_data->win, KeyPress, KeyPressMask, ft_handle_key_press, game_data);
	mlx_hook(game_data->win, KeyRelease, KeyReleaseMask, ft_handle_key_release, game_data);
}




//complete implementation of player movement

int	ft_move_forward(t_game_data *game_data)
{
	double	new_x;
	double	new_y;

	new_x = game_data->player.x_pos + game_data->player.dir_x * MOVE_SPEED;
	new_y = game_data->player.y_pos + game_data->player.dir_y * MOVE_SPEED;
	return (ft_validate_movement(game_data, new_x, new_y));
}

int	ft_move_backward(t_game_data *game_data)
{
	double	new_x;
	double	new_y;

	new_x = game_data->player.x_pos - game_data->player.dir_x * MOVE_SPEED;
	new_y = game_data->player.y_pos- game_data->player.dir_y * MOVE_SPEED;
	return (ft_validate_movement(game_data, new_x, new_y));
}

int	ft_move_left(t_game_data *game_data)
{
	double	next_x;
	double	next_y;

	next_x = game_data->player.x_pos + game_data->player.dir_y * MOVE_SPEED;
	next_y = game_data->player.y_pos - game_data->player.dir_x * MOVE_SPEED;
	return (ft_validate_movement(game_data, next_x, next_y));
}

int	ft_move_right(t_game_data *game_data)
{
	double	next_x;
	double	next_y;

	next_x = game_data->player.x_pos - game_data->player.dir_y * MOVE_SPEED;
	next_y = game_data->player.y_pos + game_data->player.dir_x * MOVE_SPEED;
	return (ft_validate_movement(game_data, next_x, next_y));
}

int	ft_move_player(t_game_data *game_data)
{
	int	moved;

	moved = 0;
	if (game_data->player.movement.move_y == 1)
		moved += ft_move_forward(game_data);
	if (game_data->player.movement.move_y == -1)
		moved += ft_move_backward(game_data);
	if (game_data->player.movement.move_x == -1)
		moved += ft_move_left(game_data);
	if (game_data->player.movement.move_x == 1)
		moved += ft_move_right(game_data);
	if (game_data->player.movement.rotate != 0)
		moved += ft_rotate_player(game_data, game_data->player.movement.rotate);
	return (moved);
}
