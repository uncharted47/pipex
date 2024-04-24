/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:03:13 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 22:05:45 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmdnotfound(char *cmd, char *message)
{
	char	*msg;

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
		return (close(fd), ft_cmdnotfound(cmdline->args[0],
				"Pipex : Directory cannot excute "), ft_lstclear(&head),
			exit(126), 1);
	if (access(cmdline->path, F_OK) == 0)
		return (close(fd), ft_cmdnotfound(cmdline->args[0],
				"Pipex : permission denied "), ft_lstclear(&head), exit(126),
			1);
	return (close(fd), ft_cmdnotfound(cmdline->args[0],
			"Pipex : Command not found "), ft_lstclear(&head), exit(127), 1);
}
