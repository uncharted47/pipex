/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:59:58 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 19:23:25 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_duphelper_heredoc(t_pipex *cmdline)
{
	if (dup2(cmdline->pipe->in, 0))
		return (1);
	if (dup2(cmdline->pipe->out, 1))
		return (1);
	close(cmdline->pipe->in);
	close(cmdline->pipe->out);
	close(cmdline->pipe->pipe[1]);
	close(cmdline->pipe->pipe[0]);
	close(cmdline->pipe->tmp);
	return (0);
}

int	ft_herlper(t_pipex *cmdline)
{
	if (pipe(cmdline->pipe->pipe))
		return (1);
	cmdline->pipe->in = cmdline->pipe->fd;
	close(cmdline->pipe->out);
	return (0);
}

int	ft_dupfiles_heredoc(t_pipex *cmdline)
{
	if (cmdline->rd_wr == 1)
	{
		if (ft_herlper(cmdline))
			return (1);
		if (pipe(cmdline->pipe->pipe))
			return (1);
		return (cmdline->pipe->out = cmdline->pipe->pipe[1],
			cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
	}
	else if (cmdline->rd_wr == 2)
	{
		(close(cmdline->pipe->pipe[1]), close(cmdline->pipe->in),
			cmdline->pipe->in = -1);
		cmdline->pipe->out = open(cmdline->file, O_CREAT | O_RDWR | O_TRUNC,
				0666);
		return (cmdline->pipe->in = cmdline->pipe->tmp, 0);
	}
	(close(cmdline->pipe->in), cmdline->pipe->in = -1);
	(close(cmdline->pipe->out), cmdline->pipe->out = -1);
	close(cmdline->pipe->pipe[1]);
	if (pipe(cmdline->pipe->pipe))
		return (1);
	return (cmdline->pipe->in = cmdline->pipe->tmp,
		cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
}

int	ft_childprocess_heredoc(t_pipex *cmdline, char **env, t_pipex *head)
{
	pid_t	id;

	if (ft_dupfiles_heredoc(cmdline))
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	id = fork();
	if (id == -1)
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	if (id == 0)
	{
		if (ft_duphelper_heredoc(cmdline))
			return (ft_lstclear(&head), perror("Pipex Error:"), exit(1), 0);
		if (execve(cmdline->path, cmdline->args, env))
			return (ft_cmdnotfound(cmdline->args[0]), ft_lstclear(&head),
				exit(1), 0);
	}
	return (id);
}

void	execute_heredoc(t_pipex *cmdline, char **env)
{
	t_pipex	*head;

	head = cmdline;
	while (cmdline)
	{
		ft_childprocess_heredoc(cmdline, env, head);
		cmdline = cmdline->next;
	}
	close(ft_lstlast(head)->pipe->in);
	close(ft_lstlast(head)->pipe->out);
	while (waitpid(-1, NULL, 0) > 0)
		;
	while (1)
		;
	ft_lstclear(&head);
	return ;
}
