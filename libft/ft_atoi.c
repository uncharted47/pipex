/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:37:05 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/05 21:34:09 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skipwhitespaces(const char *number, int *sign)
{
	while (*number == '\t' || *number == '\n' || *number == ' '
		|| *number == '\r' || *number == '\v' || *number == '\f')
		number++;
	if (*number == '-' || *number == '+')
	{
		if (*number == '-')
			*sign = -1;
		number++;
	}
	return ((char *)number);
}

int	ft_atoi(const char *num)
{
	int					sign;
	unsigned long long	n;
	int					i;

	n = 0;
	sign = 1;
	i = 0;
	num = skipwhitespaces(num, &sign);
	while (ft_isdigit(num[i]))
	{
		n = n * 10 + (num[i] - '0');
		if (n > LLONG_MAX && sign == 1)
			return (-1);
		if (n > LLONG_MAX && sign == -1)
			return (0);
		i++;
	}
	return (n * sign);
}
