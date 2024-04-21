/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:35:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 00:23:10 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_pipe(int fd, t_pipe *pipe)
{
	dprintf(fd, "Pipe: {%d, %d}\n", pipe->pipe[0], pipe->pipe[1]);
	dprintf(fd, "Out: %d\n", pipe->out);
	dprintf(fd, "Tmp: %d\n", pipe->tmp);
	dprintf(fd, "In: %d\n", pipe->in);
}

void	print_pipex(int fd, t_pipex *pipex)
{
	dprintf(fd, "Command: %s\n", pipex->cmd);
	dprintf(fd, "Arguments:\n");
	// for (int i = 0; i < 2 ; i++)
	// {
	//     dprintf(fd, "\t%s\n", pipex->args[i]);
	// }
	// dprintf(fd, "File: %s\n", pipex->file);
	dprintf(fd, "File descriptor: %d\n", pipex->fd);
	dprintf(fd, "Path: %s\n", pipex->path);
	dprintf(fd, "Read/Write: %d\n", pipex->rd_wr);
	dprintf(fd, "Pipe:\n");
	print_pipe(fd, pipex->pipe);
	dprintf(fd, "\n");
}

int	ft_duphelper(t_pipex *cmdline)
{
	dup2(cmdline->pipe->in, 0);
	dup2(cmdline->pipe->out, 1);
	dprintf(2, " child in : %d||| out : %d \n", cmdline->pipe->in,
		cmdline->pipe->out);
	return (0);
}

int	ft_dupfiles(t_pipex *cmdline, t_pipex *head)
{
	if (cmdline->rd_wr == 1)
	{
		dprintf(2, "cmd : %s || in : %d \n", cmdline->cmd, cmdline->pipe->in);
		pipe(cmdline->pipe->pipe);
		cmdline->pipe->in = open(cmdline->file, O_RDONLY);
		cmdline->pipe->out = cmdline->pipe->pipe[1];
		cmdline->pipe->tmp = cmdline->pipe->pipe[0];
		return (0);
	}
	else if (cmdline->rd_wr == 2)
	{
		dprintf(2, " 2 cmd : %s || in : %d \n", cmdline->cmd,
			cmdline->pipe->in);
		close(cmdline->pipe->pipe[1]);
		close(cmdline->pipe->in);
		cmdline->pipe->out = open(cmdline->file, O_CREAT | O_RDWR | O_TRUNC,
				0666);
		cmdline->pipe->in = cmdline->pipe->tmp;
		dprintf(2, "in : %d||| out : %d \n", cmdline->pipe->in,
			cmdline->pipe->out);
		return (0);
	}
	dprintf(2, "cmd : %s || in : %d \n", cmdline->cmd, cmdline->pipe->in);
	close(cmdline->pipe->in);
	cmdline->pipe->in = -1;
	close(cmdline->pipe->out);
	cmdline->pipe->out = -1;
	pipe(cmdline->pipe->pipe);
	cmdline->pipe->in = cmdline->pipe->tmp;
	cmdline->pipe->out = cmdline->pipe->pipe[1];
	cmdline->pipe->tmp = cmdline->pipe->pipe[0];
	return (0);
}

int	ft_childprocess(t_pipex *cmdline, char **env, t_pipex *head, pid_t *last)
{
	pid_t	id;

	if (ft_dupfiles(cmdline, head))
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	// print_pipex(2, cmdline);
	id = fork();
	if (id == -1)
		return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
	if (cmdline->rd_wr == 2)
		*last = id;
	if (id == 0)
	{
		if (ft_duphelper(cmdline))
			return (ft_lstclear(&head), perror("Error:"), exit(1), 0);
		if (execve(cmdline->path, cmdline->args, env))
			return (ft_lstclear(&head), perror("Error child:"), exit(1), 0);
	}
	// close(cmdline->pipe->tmp);
	return (1);
}

void	execute(t_pipex *cmdline, char **env)
{
	t_pipex *head;
	int status;
	pid_t last = 0;

	head = cmdline;
	while (cmdline)
	{
		dprintf(2, "cmd %s \n", cmdline->cmd);
		ft_childprocess(cmdline, env, head, &last);

		cmdline = cmdline->next;
		// if (cmdline->rd_wr == 2)
		// 	sleep(100);
	}
	close(ft_lstlast(head)->pipe->in);
	close(ft_lstlast(head)->pipe->out);
	waitpid(last, &status, 0);
	// while (1)
	// 	;
	ft_lstclear(&head);
	return ;
}