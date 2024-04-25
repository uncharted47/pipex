/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 01:37:39 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/25 22:20:31 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remove_line(char *buffer)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	new = malloc(ft_strlen(buffer) - i + 1);
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		new[j++] = buffer[i++];
	new[j] = 0;
	free(buffer);
	return (new);
}

char	*readline(char *holder)
{
	int		i;
	char	*line;

	i = 0;
	if (!*holder)
		return (NULL);
	while (holder[i] && holder[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (holder[i] && holder[i] != '\n')
	{
		line[i] = holder[i];
		i++;
	}
	if (holder[i] == '\n')
	{
		line[i] = holder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*readbuffer(char *holder, int fd, char *buffer)
{
	ssize_t	bytesread;

	bytesread = 1;
	if (!holder)
	{
		holder = malloc(1);
		*holder = 0;
	}
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (free(holder), NULL);
	*buffer = 0;
	while (!ft_strchr(buffer, '\n') && bytesread != 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(holder);
			free(buffer);
			return (NULL);
		}
		buffer[bytesread] = '\0';
		holder = ft_strjoin(holder, buffer);
	}
	return (free(buffer), holder);
}

char	*get_next_line(int fd, int flag)
{
	char		*buffer;
	char		*line;
	static char	*holder;

	buffer = NULL;
	if (flag)
		return(free(holder),NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	holder = readbuffer(holder, fd, buffer);
	if (!holder || flag)
		return (NULL);
	line = readline(holder);
	holder = remove_line(holder);
	return (line);
}
