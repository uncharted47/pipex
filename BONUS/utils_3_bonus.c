/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:03:13 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 03:56:36 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cmdnotfound(char *cmd)
{
	char	*msg;

	msg = NULL;
	msg = ft_strjoin2("Pipex : command not found ", cmd);
	if (!msg)
	{
		write(2, "Pipex : command not found \n",
			ft_strlen("Pipex : command not found \n"));
		return ;
	}
	msg = ft_strjoin(msg, " \n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	return ;
}

char	*pipecount(t_pipex *cmdline)
{
	int		i;
	int		size;
	char	*heredoc;

	size = 0;
	heredoc = NULL;
	i = 0;
	size = ft_lstsize(cmdline);
	while (i < size - 1)
	{
		heredoc = ft_strjoin(heredoc, "pipe ");
		if (!heredoc)
			return ("heredoc> ");
		i++;
	}
	heredoc = ft_strjoin(heredoc, "heredoc> ");
	if (!heredoc)
		return ("heredoc> ");
	return (heredoc);
}
