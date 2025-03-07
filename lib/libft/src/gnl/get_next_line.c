/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:19:46 by baguiar-          #+#    #+#             */
/*   Updated: 2025/01/29 21:57:20 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*fill_line(int fd, char *lchar, char *buf);
char	*put_line(char *line_buf);

char	*get_next_line(int fd)
{
	static char	*lchar[MAX_FD];
	char		*buf;
	char		*line;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buf);
		free(lchar[fd]);
		buf = NULL;
		lchar[fd] = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = fill_line(fd, lchar[fd], buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	lchar[fd] = put_line(line);
	return (line);
}

char	*fill_line(int fd, char *lchar, char *buf)
{
	ssize_t	byte;
	char	*temp;

	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == -1)
		{
			free(lchar);
			return (NULL);
		}
		else if (byte == 0)
			break ;
		buf[byte] = 0;
		if (!lchar)
			lchar = ft_strdup("");
		temp = lchar;
		lchar = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (lchar);
}

char	*put_line(char *line_buf)
{
	char	*stack;
	ssize_t	i;

	i = 0;
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
	{
		i++;
	}
	if (line_buf[i] == 0 || line_buf[1] == 0)
		return (0);
	stack = ft_substr(line_buf, i + 1, ft_strlen(line_buf) - i);
	if (*stack == 0)
	{
		free(stack);
		stack = NULL;
	}
	line_buf[i + 1] = 0;
	return (stack);
}
