/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:33:07 by dsamuel           #+#    #+#             */
/*   Updated: 2025/03/26 13:14:59 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game_data	game_data;

	if (argc != 2)
		return (ft_error_msg(NULL, ERR_USAGE, 1));
	ft_initialize_data(&game_data);
	if (ft_parse_arguments(&game_data, argv) != 0)
		return (1);
	ft_initialize_mlx_screen(&game_data);
	ft_initialize_textures(&game_data);
	ft_generate_render_images(&game_data);
	ft_setup_input_listeners(&game_data);
	mlx_loop_hook(game_data.mlx, ft_render, &game_data);
	mlx_loop(game_data.mlx);
	return (0);
}
