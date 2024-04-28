/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:35:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/28 03:27:22 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_duphelper(t_pipex *cmdline)
{
	int	status;

	status = 0;
	if (dup2(cmdline->pipe->in, 0) == -1)
		(status = 1);
	if (dup2(cmdline->pipe->out, 1) == -1)
		(status = 1);
	ft_close(cmdline->pipe->in);
	ft_close(cmdline->pipe->out);
	ft_close(cmdline->pipe->pipe[1]);
	ft_close(cmdline->pipe->pipe[0]);
	ft_close(cmdline->pipe->tmp);
	return (status);
}

int	ft_dupfiles_helper(t_pipex *cmdline)
{
	int	status;

	status = 0;
	cmdline->pipe->in = open(cmdline->file, O_RDONLY);
	if (cmdline->pipe->in == -1)
	{
		cmdline->pipe->file = cmdline->file;
		status = 1;
	}
	if (pipe(cmdline->pipe->pipe) == -1)
		(status = 1);
	return (cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], status);
}

int	ft_dupfiles(t_pipex *cmdline)
{
	if (cmdline->rd_wr == 1)
		return (ft_dupfiles_helper(cmdline));
	else if (cmdline->rd_wr == 2)
	{
		(ft_close(cmdline->pipe->pipe[1]), ft_close(cmdline->pipe->in),
			cmdline->pipe->in = -1);
		cmdline->pipe->out = open(cmdline->file, O_CREAT | O_RDWR | O_TRUNC,
				0666);
		if (cmdline->pipe->out == -1)
			return (ft_close(cmdline->pipe->tmp),
				cmdline->pipe->file = cmdline->file, 1);
		return (cmdline->pipe->in = cmdline->pipe->tmp, 0);
	}
	(ft_close(cmdline->pipe->in), cmdline->pipe->in = -1);
	(ft_close(cmdline->pipe->out), cmdline->pipe->out = -1);
	ft_close(cmdline->pipe->pipe[1]);
	if (pipe(cmdline->pipe->pipe) == -1)
		return (1);
	return (cmdline->pipe->in = cmdline->pipe->tmp,
		cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
}

int	ft_childprocess(t_pipex *cmdline, char **env, t_pipex *head)
{
	int	fd;
	int	status;

	fd = 0;
	status = 0;
	if (ft_dupfiles(cmdline))
		(perror(cmdline->pipe->file), status = 1);
	cmdline->id = fork();
	if (cmdline->id == -1)
		return (ft_lstclear(&head), exit(1), 0);
	if (cmdline->id == 0)
	{
		if (ft_duphelper(cmdline) && status)
			return (ft_lstclear(&head), exit(1), 1);
		if (ft_strlen(cmdline->path) == 0)
			(ft_cmdnotfound(cmdline->path, CMDNF), ft_lstclear(&head),
				exit(127), write(2, "here \n", ft_strlen("here \n")));
		if (!ispath(cmdline->path) && cmdline->pipe->env)
			return (ft_cmdnotfound(cmdline->args[0], CMDNF), ft_lstclear(&head),
				exit(127), 1);
		if (execve(cmdline->path, cmdline->args, env))
			ft_exitstatus(cmdline, head, fd);
	}
	return (0);
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
	ft_close(ft_lstlast(head)->pipe->in);
	ft_close(ft_lstlast(head)->pipe->out);
	cmdline = head;
	while (cmdline)
	{
		waitpid(cmdline->id, &status, 0);
		cmdline = cmdline->next;
	}
	ft_lstclear(&head);
	return ((status >> 8) & 0x0000ff);
}
