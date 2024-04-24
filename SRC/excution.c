/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:35:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 18:46:20 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_duphelper(t_pipex *cmdline)
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

int	ft_dupfiles_helper(t_pipex *cmdline)
{
	int	status;

	status = 0;
	cmdline->pipe->in = open(cmdline->file, O_RDONLY);
	if (cmdline->pipe->in == -1)
		(cmdline->pipe->file = cmdline->file, status = 1);
	if (pipe(cmdline->pipe->pipe) == -1)
		return (1);
	return (cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], status);
}

int	ft_dupfiles(t_pipex *cmdline)
{
	if (cmdline->rd_wr == 1)
		return (ft_dupfiles_helper(cmdline));
	else if (cmdline->rd_wr == 2)
	{
		(close(cmdline->pipe->pipe[1]), close(cmdline->pipe->in),
			cmdline->pipe->in = -1);
		cmdline->pipe->out = open(cmdline->file, O_CREAT | O_RDWR | O_TRUNC,
				0666);
		if (cmdline->pipe->out == -1)
			return (1);
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

int	ft_childprocess(t_pipex *cmdline, char **env, t_pipex *head)
{
	pid_t	id;
	int		fd;

	if (ft_dupfiles(cmdline))
		return (perror(cmdline->pipe->file), 1);
	id = fork();
	if (id == -1)
		return (ft_lstclear(&head), perror("Pipex Error"), exit(11), 0);
	cmdline->id = id;
	if (id == 0)
	{
		if (ft_duphelper(cmdline))
			return (ft_lstclear(&head), perror("Pipex Error"), exit(1), 1);
		if (execve(cmdline->path, cmdline->args, env))
		{
			fd = open(cmdline->args[0], __O_DIRECTORY) != -1;
			if (fd != -1)
				return (close(fd), ft_cmdnotfound(cmdline->args[0]),
					ft_lstclear(&head), exit(126), 1);
			return (ft_cmdnotfound(cmdline->args[0]), ft_lstclear(&head),
				exit(127), 1);
		}
	}
	return (id);
}

int	execute(t_pipex *cmdline, char **env)
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
	return (WEXITSTATUS(status));
}
