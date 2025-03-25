#include "cub3d.h"

//move mlx initaizlization folder files


void	ft_initialize_image(t_game_data *game_data, t_img_data *image, int width, int height)
{
	// ft_initialize_img_data(image);
	// image->img = mlx_new_image(game_data->mlx, width, height);
	// if (image->img == NULL)
	// 	ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MLX_IMG, 1));
	// image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
	// 		&image->size_line, &image->endian);
	// return ;
	if (!game_data || !image || !game_data->mlx)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MLX_IMG, 1));
	ft_initialize_img_data(image);
	image->img = mlx_new_image(game_data->mlx, width, height);
	if (!image->img)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MLX_IMG, 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	if (!image->addr)
		ft_clean_and_exit(game_data, ft_error_msg(NULL, ERR_MLX_IMG, 1));
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