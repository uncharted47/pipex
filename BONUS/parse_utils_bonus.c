/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:11 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/28 02:37:14 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_cmdpath(char *path, char *cmd)
{
	char	**split;
	char	*new;
	char	*tmp;
	char	**cmdsplit;

	split = NULL;
	if (!ft_strlen(cmd))
		return (free(cmd), tmp = ft_strdup(""), tmp);
	cmdsplit = ft_split(cmd, WSP);
	if (!cmdsplit)
		return (cmd);
	tmp = ft_strdup(cmdsplit[0]);
	if (ispath(tmp))
		return (free(cmd), failsafe(cmdsplit), tmp);
	free(tmp);
	new = ft_strjoin(ft_strdup("/"), cmdsplit[0]);
	if (path)
		split = ft_split((path + 5), ":");
	if (!split)
		return (free(new), failsafe(cmdsplit), cmd);
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

	if (!cmd)
		return (NULL);
	i = ft_strlen(cmd) - 1;
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
