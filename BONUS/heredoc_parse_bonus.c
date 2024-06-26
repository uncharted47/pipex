/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:04:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/26 00:16:55 by elyzouli         ###   ########.fr       */
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

void	ft_writeheredoc(char *holder)
{
	int	fd;

	unlink("/tmp/heredoc");
	fd = open("/tmp/heredoc", O_CREAT | O_TRUNC | O_RDWR, 0664);
	if (fd == -1)
		return (free(holder));
	write(fd, holder, ft_strlen(holder));
	ft_close(fd);
	return (free(holder));
}

void	ft_readheredoc(t_pipex *cmdline)
{
	char	*line;
	char	*holder;
	char	*heredoc;

	holder = NULL;
	heredoc = pipecount(cmdline);
	line = NULL;
	while (1)
	{
		(write(1, heredoc, ft_strlen(heredoc)), line = get_next_line(0, 0));
		if (!line)
			return (ft_writeheredoc(holder), free(heredoc));
		if (!ft_strncmp(line, cmdline->delimiter, ft_strlen(cmdline->delimiter))
			&& (ft_strlen(line) - 1) == ft_strlen(cmdline->delimiter))
		{
			get_next_line(0, 1);
			free(line);
			break ;
		}
		holder = ft_strjoin(holder, line);
		if (!holder)
			return (free(line));
		free(line);
	}
	return (ft_writeheredoc(holder), free(heredoc));
}

int	ft_findfiles_heredoc(t_pipex *cmdline, char **str)
{
	size_t	i;

	i = 0;
	cmdline->rd_wr = 1;
	cmdline->delimiter = str[0];
	cmdline->file = "/tmp/heredoc";
	cmdline = ft_lstlast(cmdline);
	i = get_outfile(str);
	cmdline->rd_wr = 2;
	cmdline->file = str[i];
	return (1);
}

t_pipex	*parse_heredoc(char **str, char **env, int cmd)
{
	t_pipex	*pipe;

	pipe = NULL;
	if (cmd < 6)
		return (ft_exit("Pipex : not enough arguments \n"), NULL);
	pipe = create_linecmd((str + 1), env);
	if (!pipe || !pipe->pipe)
		return (ft_lstclear(&pipe),
			ft_exit("Pipex Error: allocation failed \n"), NULL);
	ft_findfiles_heredoc(pipe, str);
	ft_readheredoc(pipe);
	return (pipe);
}
