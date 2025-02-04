/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:19:48 by baguiar-          #+#    #+#             */
/*   Updated: 2024/03/21 21:59:38 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	**ft_free(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

static int	ft_word_count(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*cp_words(char *word, char const *s, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		word[j] = s[i - len];
		j++;
		len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**sp_words(char const *s, char c, char **s2, int nword)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	word = 0;
	len = 0;
	while (word < nword)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		s2[word] = (char *)malloc(sizeof(char) * (len + 1));
		if (!s2[word])
			return (ft_free(s2, word));
		cp_words(s2[word], s, i, len);
		len = 0;
		word++;
	}
	s2[word] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	nwords;

	if (!s)
		return (0);
	nwords = ft_word_count(s, c);
	s2 = (char **)malloc(sizeof(char *) * (nwords + 1));
	if (!s2)
		return (0);
	s2 = sp_words(s, c, s2, nwords);
	return (s2);
}
