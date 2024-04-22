/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:35:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 16:45:11 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_duphelper(t_pipex *cmdline)
{
	dup2(cmdline->pipe->in, 0);
	dup2(cmdline->pipe->out, 1);
	close(cmdline->pipe->in);
	close(cmdline->pipe->out);
	close(cmdline->pipe->pipe[1]);
	close(cmdline->pipe->pipe[0]);
	close(cmdline->pipe->tmp);
	return (0);
}

int	ft_dupfiles(t_pipex *cmdline, t_pipex *head)
{
	if (cmdline->rd_wr == 1)
	{
		pipe(cmdline->pipe->pipe);
		cmdline->pipe->in = open(cmdline->file, O_RDONLY);
		return (cmdline->pipe->out = cmdline->pipe->pipe[1],
			cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
	}
	else if (cmdline->rd_wr == 2)
	{
		close(cmdline->pipe->pipe[1]);
		close(cmdline->pipe->in);
		cmdline->pipe->in = -1;
		cmdline->pipe->out = open(cmdline->file, O_CREAT | O_RDWR | O_TRUNC,
				0666);
		return (cmdline->pipe->in = cmdline->pipe->tmp, 0);
	}
	close(cmdline->pipe->in);
	cmdline->pipe->in = -1;
	close(cmdline->pipe->out);
	cmdline->pipe->out = -1;
	close(cmdline->pipe->pipe[1]);
	pipe(cmdline->pipe->pipe);
	return (cmdline->pipe->in = cmdline->pipe->tmp,
		cmdline->pipe->out = cmdline->pipe->pipe[1],
		cmdline->pipe->tmp = cmdline->pipe->pipe[0], 0);
}

int	ft_childprocess(t_pipex *cmdline, char **env, t_pipex *head)
{
	pid_t	id;

	if (ft_dupfiles(cmdline, head))
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	id = fork();
	if (id == -1)
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	if (id == 0)
	{
		if (ft_duphelper(cmdline))
			return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
		if (execve(cmdline->path, cmdline->args, env))
			return (ft_lstclear(&head), perror("Error child:"), exit(1), 0);
	}
	return (id);
}

void	execute(t_pipex *cmdline, char **env)
{
	t_pipex	*head;
	int		status;

	head = cmdline;
	while (cmdline)
	{
		ft_childprocess(cmdline, env, head);
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
