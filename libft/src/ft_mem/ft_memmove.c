/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:26:58 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 22:03:01 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	s1 = (char *)dest;
	s2 = (char *)src;
	if (dest == src)
		return (dest);
	if (s1 > s2)
	{
		while (n--)
			s1[n] = s2[n];
	}
	else
	{
		while (n--)
		{
			*s1++ = *s2++;
		}
	}
	return (dest);
}
