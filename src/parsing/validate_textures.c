#include "cub3d.h"

int	ft_validate_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_error_val(rgb[i], ERR_TEX_RGB_VAL, STATUS_FAIL));
		i++;
	}
	return (STATUS_OK);
}

unsigned long	ft_convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	ft_validate_textures_map(t_game_data *game_data, t_texture_data *textures)
{
	if (!textures->texture_config.no_texture_path || !textures->texture_config.so_texture_path || !textures->texture_config.we_texture_path
		|| !textures->texture_config.ea_texture_path)
		return (ft_error_msg(game_data->map_data.path, ERR_TEX_MISSING, STATUS_FAIL));
	if (!textures->texture_config.floor_color || !textures->texture_config.ceiling_color)
		return (ft_error_msg(game_data->map_data.path, ERR_COLOR_MISSING, STATUS_FAIL));
	if (ft_file_and_dir_checker(textures->texture_config.no_texture_path, false) == STATUS_FAIL
		|| ft_file_and_dir_checker(textures->texture_config.so_texture_path, false) == STATUS_FAIL
		|| ft_file_and_dir_checker(textures->texture_config.we_texture_path, false) == STATUS_FAIL
		|| ft_file_and_dir_checker(textures->texture_config.ea_texture_path, false) == STATUS_FAIL
		|| ft_validate_rgb(textures->texture_config.floor_color) == STATUS_FAIL
		|| ft_validate_rgb(textures->texture_config.ceiling_color) == STATUS_FAIL)
		return (STATUS_FAIL);
	textures->hex_floor = ft_convert_rgb_to_hex(textures->texture_config.floor_color);
	textures->hex_ceiling = ft_convert_rgb_to_hex(textures->texture_config.ceiling_color);
	return (STATUS_OK);
}
