/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:03:13 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/25 21:31:14 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cmdnotfound(char *cmd, char *message)
{
	char	*msg;

	if (!cmd)
	{
		cmd = "";
		message = "Pipex : permission denied: ";
	}
	msg = ft_strdup(message);
	msg = ft_strjoin(msg, cmd);
	if (!msg)
	{
		write(2, msg, ft_strlen(msg));
		return ;
	}
	msg = ft_strjoin(msg, " \n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	return ;
}

int	ft_exitstatus(t_pipex *cmdline, t_pipex *head, int fd)
{
	fd = open(cmdline->args[0], __O_DIRECTORY);
	if (fd != -1)
		return (ft_close(fd), ft_cmdnotfound(cmdline->args[0],
				"Pipex : Directory cannot excute "), ft_lstclear(&head),
			exit(126), 1);
	if ((access(cmdline->args[0], F_OK) == 0 && access(cmdline->args[0], X_OK) ==
		-1) || (!cmdline->path && cmdline->pipe->env))
		return (ft_close(fd), ft_cmdnotfound(cmdline->args[0],
				"Pipex : permission denied "), ft_lstclear(&head), exit(126),
			1);
	return (ft_close(fd), ft_cmdnotfound(cmdline->args[0],
			"Pipex : Command not found "), ft_lstclear(&head), exit(127), 1);
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

int	ispath(char *cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void ft_close(int fd)
{
	if(fd == -1)
		return;
	close(fd);
	return ;
}
