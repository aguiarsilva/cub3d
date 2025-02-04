/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:39:42 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 21:39:42 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_ptrlen(unsigned long long p)
{
	int	i;

	i = 0;
	while (p != 0)
	{
		p /= 16;
		i++;
	}
	return (i);
}

static void	ft_putp(unsigned long long p)
{
	if (p >= 16)
	{
		ft_putp(p / 16);
		ft_putp(p % 16);
	}
	else
	{
		if (p <= 9)
			ft_putchar_fd((p + '0'), 1);
		else
			ft_putchar_fd((p - 10 + 'a'), 1);
	}
}

int	ft_printf_p(unsigned long long p)
{
	int	p_out;

	p_out = 0;
	p_out += write(1, "0x'", 2);
	if (p == 0)
	{
		ft_putchar_fd('0', 1);
		return (3);
	}
	else
	{
		ft_putp(p);
		p_out += ft_ptrlen(p);
	}
	return (p_out);
}
