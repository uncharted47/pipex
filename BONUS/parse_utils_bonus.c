/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:11 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 22:18:37 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_cmdpath(char *path, char *cmd)
{
	char	**split;
	char	*new;
	char	*tmp;
	char	**cmdsplit;
	size_t	i;

	i = 0;
	cmdsplit = ft_split(cmd, WSP);
	new = ft_strjoin(ft_strdup("/"), cmdsplit[0]);
	if (access(cmdsplit[0], F_OK | X_OK) != -1)
	{
		tmp = ft_strdup(cmdsplit[0]);
		failsafe(cmdsplit);
		free(new);
		free(cmd);
		return (tmp);
	}
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
	if (ft_strlen(cmd) == i + 1)
		return (ft_strdup(cmd));
	str = ft_strdup(cmd);
	while (i && str[i] != '/')
		i--;
	if (str[i] == '/')
		result = ft_strdup(&str[i + 1]);
	else
		result = ft_strdup(&str[i]);
	return (free(str), result);
}

int	ft_findfiles(t_pipex *cmdline, char **str)
{
	size_t	i;

	i = 0;
	cmdline->rd_wr = 1;
	cmdline->file = str[i];
	cmdline = ft_lstlast(cmdline);
	i = get_outfile(str);
	cmdline->rd_wr = 2;
	cmdline->file = str[i];
	return (1);
}
