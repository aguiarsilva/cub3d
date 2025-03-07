/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:54:41 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 22:03:24 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nlst;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		nlst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nlst;
	}
}
