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

int	ft_error_val(int arg, char *str, int er_code)
{
	ft_putstr_fd(RED "cub3D: Error: ", 2);
	ft_putnbr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n" RESET, 2);
	return (er_code);
}