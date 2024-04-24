/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:03:13 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 21:59:46 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmdnotfound(char *cmd)
{
	char	*msg;

	msg = NULL;
	msg = ft_strjoin2("Pipex : command not found ", cmd);
	if (!msg)
	{
		write(2, "Pipex : command not found",
			ft_strlen("Pipex : command not found"));
		return ;
	}
	msg = ft_strjoin(msg, " \n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	return ;
}
