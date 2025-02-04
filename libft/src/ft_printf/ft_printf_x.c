/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:40:17 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 21:40:17 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_hexlen(unsigned int num)
{
	int	i;

	i = 0;
	while (num != 0)
	{
		num /= 16;
		i++;
	}
	return (i);
}

static void	ft_putx(unsigned int num, const char fmt)
{
	if (num >= 16)
	{
		ft_putx(num / 16, fmt);
		ft_putx(num % 16, fmt);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (fmt == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			else if (fmt == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_printf_x(unsigned int num, const char fmt)
{
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	else
		ft_putx(num, fmt);
	return (ft_hexlen(num));
}
