/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:23:59 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/07 18:49:05 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	sizedest;
	size_t	i;
	size_t	result;

	if (size == 0)
		return (ft_strlen(src));
	if (size > ft_strlen(dest))
		result = ft_strlen(dest) + ft_strlen(src);
	else
		result = size + ft_strlen(src);
	sizedest = ft_strlen(dest);
	i = 0;
	while (src[i] && (i + sizedest) < size - 1)
	{
		dest[sizedest + i] = src[i];
		i++;
	}
	dest[sizedest + i] = '\0';
	return (result);
}
