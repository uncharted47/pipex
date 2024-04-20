/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:20:38 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/05 21:32:44 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*point;
	size_t	end;

	i = 0;
	point = NULL;
	end = ft_strlen(str);
	if ((char)c == '\0')
	{
		point = (char *)&str[end];
		return (point);
	}
	while (str[i])
	{
		if (str[i] == (char)c)
			point = (char *)&str[i];
		i++;
	}
	if (point && *point == (char)c)
		return (point);
	return (NULL);
}
