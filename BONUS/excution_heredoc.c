/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:35:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 03:55:49 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_duphelper(t_pipex *cmdline)
{
	if (dup2(cmdline->pipe->in, 0) == -1)
		return (1);
	if (dup2(cmdline->pipe->out, 1) == -1)
		return (1);
	close(cmdline->pipe->in);
	close(cmdline->pipe->out);
	close(cmdline->pipe->pipe[1]);
	close(cmdline->pipe->pipe[0]);
	close(cmdline->pipe->tmp);
	return (0);
}

static int	ft_dupfiles_helper(t_pipex *cmdline)
{
	cmdline->pipe->in = open(cmdline->file, O_RDONLY);
	if (pipe(cmdline->pipe->pipe) == -1)
		return (1);
	return (cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
}

static int	ft_dupfiles(t_pipex *cmdline)
{
	if (cmdline->rd_wr == 1)
		return (ft_dupfiles_helper(cmdline));
	else if (cmdline->rd_wr == 2)
	{
		(close(cmdline->pipe->pipe[1]), close(cmdline->pipe->in),
			cmdline->pipe->in = -1);
		cmdline->pipe->out = open(cmdline->file, O_CREAT | O_RDWR | O_APPEND,
				0666);
		return (cmdline->pipe->in = cmdline->pipe->tmp, 0);
	}
	(close(cmdline->pipe->in), cmdline->pipe->in = -1);
	(close(cmdline->pipe->out), cmdline->pipe->out = -1);
	close(cmdline->pipe->pipe[1]);
	if (pipe(cmdline->pipe->pipe) == -1)
		return (1);
	return (cmdline->pipe->in = cmdline->pipe->tmp,
		cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
}

static int	ft_childprocess(t_pipex *cmdline, char **env, t_pipex *head)
{
	pid_t	id;

	if (ft_dupfiles(cmdline))
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	id = fork();
	if (id == -1)
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	if (id == 0)
	{
		if (ft_duphelper(cmdline))
			return (ft_lstclear(&head), perror("Pipex Error here"), exit(1), 0);
		if (execve(cmdline->path, cmdline->args, env))
			return (ft_cmdnotfound(cmdline->args[0]), ft_lstclear(&head),
				exit(1), 0);
	}
	return (id);
}

int	execute_heredoc(t_pipex *cmdline, char **env)
{
	t_pipex	*head;
	int		status;

	status = 1;
	head = cmdline;
	while (cmdline)
	{
		ft_childprocess(cmdline, env, head);
		cmdline = cmdline->next;
	}
	close(ft_lstlast(head)->pipe->in);
	close(ft_lstlast(head)->pipe->out);
	cmdline = head;
	while (cmdline)
	{
		waitpid(cmdline->id, &status, 0);
		cmdline = cmdline->next;
	}
	ft_lstclear(&head);
	unlink("/tmp/heredoc");
	return (WEXITSTATUS(status));
}