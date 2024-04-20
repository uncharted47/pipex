/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:46:50 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/11 02:14:49 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	if (!pointer1 && !pointer2)
		return (0);
	str1 = (const unsigned char *)pointer1;
	str2 = (const unsigned char *)pointer2;
	i = 0;
	while ((str1 || str2) && i < n)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		i++;
		str1++;
		str2++;
	}
	return (0);
}
