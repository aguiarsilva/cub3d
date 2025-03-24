#include "cub3d.h"

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