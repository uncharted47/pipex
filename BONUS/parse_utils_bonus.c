/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:11 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 17:16:04 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_cmdpath(char *path, char *cmd)
{
	char	**split;
	char	*new;
	char	**cmdsplit;
	size_t	i;

	i = 0;
	cmdsplit = ft_split(cmd, WSP);
	new = ft_strjoin(ft_strdup("/"), cmdsplit[0]);
	split = ft_split((path + 5), ":");
	if (!split)
		return (perror("Error:"), free(new), free(cmdsplit), NULL);
	return (cmdpath_helper(split, cmdsplit, cmd, new));
}

char	*get_envpath(char **env)
{
	size_t	i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

size_t	get_outfile(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return ((i - 1));
}

char	*ft_removepath(char *cmd)
{
	size_t	i;
	char	*str;
	char	*result;

	i = ft_strlen(cmd) - 1;
	if (ft_strlen(cmd) == 1)
		return (ft_strdup(cmd));
	str = ft_strdup(cmd);
	while (i && str[i] != '/')
		i--;
	result = ft_strdup(&str[i + 1]);
	return (free(str), result);
}

int	ft_findfiles(t_pipex *cmdline, char **str)
{
	size_t	i;
	ssize_t	fd;

	fd = -1;
	i = 0;
	fd = open(str[i], O_RDONLY);
	if (fd == -1)
		return (0);
	cmdline->rd_wr = 1;
	cmdline->pipe->fd = fd;
	cmdline->file = str[i];
	cmdline = ft_lstlast(cmdline);
	i = get_outfile(str);
	fd = open(str[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		return (0);
	close(fd);
	cmdline->rd_wr = 2;
	cmdline->file = str[i];
	return (1);
}
