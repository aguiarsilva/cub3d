/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:39:13 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 21:39:13 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_putchar_c(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_s(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		return (write(1, "(null)", 6));
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putint_d_i(int num)
{
	int	i;

	i = 0;
	if (num < -9 || num > 9)
		i += ft_putint_d_i(num / 10);
	else if (num < 0)
		i += ft_putchar_c('-');
	if (num < 0)
		i += ft_putchar_c((num % 10 * -1) + '0');
	else if (num >= 0)
		i += ft_putchar_c(num % 10 + '0');
	return (i);
}

int	ft_putunint_u(unsigned int u)
{
	int	i;

	i = 0;
	if (u > 9)
		i += ft_putunint_u(u / 10);
	i += ft_putchar_c(u % 10 + '0');
	return (i);
}
