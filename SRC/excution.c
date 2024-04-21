/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:35:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/21 18:37:10 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_pipe(t_pipe *pipe)
{
	printf("pipe[0]: %d\n", pipe->pipe[0]);
	printf("pipe[1]: %d\n", pipe->pipe[1]);
	printf("out: %d\n", pipe->out);
	printf("tmp: %d\n", pipe->tmp);
	printf("in: %d\n", pipe->in);
}

int	ft_duphelper(t_pipex *cmdline)
{
	dup2(cmdline->pipe->in, 0);
	dup2(cmdline->pipe->out, 1);
	close(cmdline->pipe->in);
	close(cmdline->pipe->out);
	close(cmdline->pipe->pipe[1]);
	close(cmdline->pipe->pipe[0]);
	return (0);
}

int	ft_dupfiles(t_pipex *cmdline, t_pipex *head)
{
	if (cmdline->rd_wr == 1)
	{
		pipe(cmdline->pipe->pipe);
		cmdline->pipe->in = cmdline->fd;
		cmdline->pipe->out = cmdline->pipe->pipe[1];
		cmdline->pipe->tmp = cmdline->pipe->pipe[0];
		return (0);
	}
	if (cmdline->rd_wr == 2)
	{
		close(cmdline->pipe->pipe[1]);
		cmdline->pipe->in = cmdline->pipe->tmp;
		cmdline->pipe->out = cmdline->fd;
		return (0);
	}
	close(cmdline->pipe->in);
	close(cmdline->pipe->out);
	pipe(cmdline->pipe->pipe);
	cmdline->pipe->in = cmdline->pipe->tmp;
	cmdline->pipe->out = cmdline->pipe->pipe[1];
	cmdline->pipe->tmp = cmdline->pipe->pipe[0];
	return (0);
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
			return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	}
	// close(cmdline->pipe->tmp);
	return (1);
}

void	execute(t_pipex *cmdline, char **env)
{
	t_pipex *head;
	int status;

	head = cmdline;
	while (cmdline)
	{
		ft_childprocess(cmdline, env, head);
		close(ft_lstlast(head)->fd);
		close(ft_lstlast(head)->pipe->tmp);
		close(head->fd);
		close(ft_lstlast(head)->pipe->pipe[0]);
		close(ft_lstlast(head)->pipe->pipe[1]);
		cmdline = cmdline->next;
	}
	while (wait(NULL) > 0)
		;

	ft_lstclear(&head);
	return ;
}