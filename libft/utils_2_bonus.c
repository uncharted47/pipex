/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:54:50 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/27 20:21:33 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*joined;
	size_t	length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (length + 2));
	if (!joined)
		return (NULL);
	*joined = '\0';
	ft_strcat((char *)joined, s1);
	ft_strcat((char *)joined, s2);
	return (joined);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	length;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		*s1 = '\0';
	}
	length = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (length + 1));
	if (!joined)
		return (NULL);
	*joined = '\0';
	ft_strcat((char *)joined, s1);
	ft_strcat((char *)joined, s2);
	free(s1);
	return (joined);
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	if (str == NULL)
	{
		return (NULL);
	}
	size = ft_strlen((char *)str);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	isdir(char *cmd)
{
	char	*msg;

	msg = ft_strdup("Pipex :");
	msg = ft_strjoin(msg, cmd);
	msg = ft_strjoin(msg, ": Is a directory \n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	return ;
}
