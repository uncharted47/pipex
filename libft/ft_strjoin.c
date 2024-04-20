/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:09:57 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/04 21:04:12 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	size;

	size = ft_strlen((char *)dest);
	i = 0;
	while (src[i])
	{
		dest[size + i] = src[i];
		i++;
	}
	dest[size + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (length + 1));
	if (!joined)
		return (NULL);
	*joined = '\0';
	ft_strcat((char *)joined, s1);
	ft_strcat((char *)joined, s2);
	return (joined);
}
