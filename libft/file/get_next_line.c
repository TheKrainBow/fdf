/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:43:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/07 01:00:42 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_file(int fd, char **dest)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_return;
	char	*tmp;

	read_return = BUFFER_SIZE;
	while (read_return == BUFFER_SIZE && ft_strchr(*dest, '\n') == NULL)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = 0;
		tmp = *dest;
		*dest = ft_strjoin(*dest, buffer);
		free(tmp);
	}
	return (read_return);
}

char	*get_next_line(int fd)
{
	static char	*buffer[200];
	char		*next_nl;
	char		*dest;
	char		*tmp;
	int			read_return;

	dest = NULL;
	read_return = read_file(fd, buffer + fd);
	if (buffer[fd][0] == 0)
		return (NULL);
	next_nl = ft_strchr(buffer[fd], '\n');
	if (next_nl == NULL || read_return < BUFFER_SIZE)
	{
		dest = ft_strndup(buffer[fd], ft_strlen(buffer[fd]));
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (dest);
	}
	dest = ft_strndup(buffer[fd], next_nl - buffer[fd] + 1);
	tmp = buffer[fd];
	buffer[fd] = ft_strndup(next_nl + 1, ft_strlen(next_nl + 1));
	free(tmp);
	return (dest);
}
