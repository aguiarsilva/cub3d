/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:37:32 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 21:37:32 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_fmt(va_list ap, const char fmt)
{
	int	out_len;

	out_len = 0;
	if (fmt == 'c')
	{
		out_len += ft_putchar_c(va_arg(ap, int));
	}
	else if (fmt == 's')
		out_len += ft_putstr_s(va_arg(ap, char *));
	else if (fmt == 'd' || fmt == 'i')
		out_len += ft_putint_d_i((long)va_arg(ap, int));
	else if (fmt == 'x' || fmt == 'X')
		out_len += ft_printf_x(va_arg(ap, unsigned int), fmt);
	else if (fmt == 'u')
		out_len += ft_putunint_u(va_arg(ap, unsigned int));
	else if (fmt == 'p')
		out_len += ft_printf_p(va_arg(ap, unsigned long long));
	else if (fmt == '%')
		out_len += ft_putchar_c('%');
	return (out_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		out;

	va_start(ap, format);
	i = 0;
	out = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			out += ft_putchar_c(format[i]);
		}
		else
			out += ft_fmt(ap, format[++i]);
		i++;
	}
	va_end(ap);
	return (out);
}
