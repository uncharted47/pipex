/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:04:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 22:48:34 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_outfilehere_doc(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (cmd[i - 1]);
}

void	ft_readheredoc(t_pipex *cmdline)
{
	char	*line;
	int		fd[2];

	if (pipe(fd))
		return ;
	cmdline->pipe->fd = fd[0];
	dprintf(2, "%d \n", cmdline->pipe->fd);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, cmdline->delimiter, ft_strlen(cmdline->delimiter))
			&& (ft_strlen(line) - 1) == ft_strlen(cmdline->delimiter))
		{
			close(fd[1]);
			free(line);
			return ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	return ;
}

int	ft_findfiles_heredoc(t_pipex *cmdline, char **str)
{
	size_t	i;

	i = 0;
	cmdline->rd_wr = 1;
	cmdline->delimiter = str[i];
	cmdline = ft_lstlast(cmdline);
	cmdline->rd_wr = 2;
	cmdline->file = get_outfilehere_doc(str);
	return (1);
}

t_pipex	*parse_heredoc(char **str, char **env)
{
	t_pipex *pipe;

	pipe = NULL;
	pipe = create_linecmd((str + 1), env);
	if (!pipe || !pipe->pipe)
		return (ft_lstclear(&pipe), ft_exit("Pipex Error: allocation failed"),
			NULL);
	ft_findfiles_heredoc(pipe, str);
	if (ft_lstsize(pipe) < 2)
	{
		ft_lstclear(&pipe);
		ft_exit("Pipex : atleast 2 commands for 1 pipe \n");
		return (0);
	}
	ft_readheredoc(pipe);
	return (pipe);
}