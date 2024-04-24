/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 06:42:47 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 20:27:43 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
