/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:10:43 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/07 02:42:25 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numberlength(int n)
{
	long long	number;
	size_t		size;

	number = n;
	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		number *= -1;
		size++;
	}
	while (number)
	{
		number /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*number;
	size_t		size;
	long long	num;

	size = numberlength(n);
	num = n;
	number = (char *)malloc(sizeof(char) * (size + 1));
	if (!number)
		return (NULL);
	if (n == 0)
		number[0] = '0';
	if (n < 0)
	{
		num *= -1;
		number[0] = '-';
	}
	number[size] = '\0';
	size--;
	while (num)
	{
		number[size] = ((num % 10) + '0');
		num /= 10;
		size--;
	}
	return (number);
}
