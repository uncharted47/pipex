/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:11:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 18:53:53 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_isalnum(int car)
{
	if (ft_isalpha(car) || ft_isdigit(car))
		return (1);
	return (0);
}
