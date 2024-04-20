/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 06:42:47 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/19 21:35:35 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_sep(char c, char *sep)
{
	size_t	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}

char	*ft_strcat2(char *dest, const char *src)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(dest);
	i = 0;
	dest[size] = ' ';
	while (src[i])
	{
		dest[size + 1 + i] = src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
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
	int i;
	int size;
	char *dup;

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