/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:25:51 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 22:02:39 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			len;
	unsigned char	*ptr;

	len = 0;
	ptr = (unsigned char *)s;
	while (len < n)
	{
		ptr[len] = 0;
		len++;
	}
}
