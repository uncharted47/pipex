/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:14:20 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/10 21:21:25 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(to_find) > ft_strlen(str))
		return (NULL);
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	if (ft_strlen(to_find) > n)
		return (NULL);
	while (str[i] && i < n)
	{
		if (ft_strncmp(&str[i], to_find, ft_strlen(to_find)) == 0)
		{
			if ((i + ft_strlen(to_find)) <= n)
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
