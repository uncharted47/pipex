/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:53:11 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/09 21:22:33 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*mem;

	if (elementSize && elementCount >= SIZE_MAX / elementSize)
		return (NULL);
	mem = malloc(elementCount * elementSize);
	if (!mem)
		return (NULL);
	ft_bzero(mem, (elementCount * elementSize));
	return (mem);
}
