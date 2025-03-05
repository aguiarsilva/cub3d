/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamuel <dsamuel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:33:07 by dsamuel           #+#    #+#             */
/*   Updated: 2025/03/05 19:49:15 by dsamuel          ###   ########.fr       */
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


int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 2)
        return (ft_error_msg(NULL, ERR_USAGE, 1));

    // Initialize game data and start the game loop here
    // ...
    
}