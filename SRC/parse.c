/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:34:00 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 16:46:55 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cmdpath_helper(char **split, char **cmdsplit, char *cmd, char *new)
{
	char	*line;
	size_t	i;

	i = 0;
	while (split[i])
	{
		line = ft_strjoin2(split[i], new);
		if (!line)
			return (failsafe(split), free(cmd), failsafe(cmdsplit),
				perror("Error:"), free(new), NULL);
		if (!access(line, F_OK | X_OK))
			return (failsafe(split), free(cmd), failsafe(cmdsplit), free(new),
				line);
		free(line);
		i++;
	}
	return (failsafe(split), failsafe(cmdsplit), free(new), cmd);
}

char	**ft_getargs(char *str, char *cmd)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	**arr;

	i = 0;
	tmp = ft_strtrim(str, WSP);
	if (!tmp)
		return (NULL);
	while (ft_isalnum(tmp[i]))
		i++;
	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		return (perror("ERROR:"), NULL);
	arr[0] = ft_removepath(cmd);
	if (i == ft_strlen(tmp))
		return (arr[1] = NULL, free(tmp), arr);
	tmp2 = ft_strtrim(&tmp[i], WSP);
	arr[1] = ft_strdup(tmp2);
	if (!arr[1])
		return (free(arr[0]), free(tmp), free(tmp2), free(arr),
			perror("Error :"), NULL);
	arr[2] = NULL;
	return (free(tmp), free(tmp2), arr);
}

t_pipe	*ft_initpipe(void)
{
	static t_pipe	*new = NULL;

	if (new)
		return (new);
	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->in = -1;
	new->out = -1;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	new->tmp = -1;
	return (new);
}

t_pipex	*create_linecmd(char **cmd, char **env)
{
	size_t	i;
	size_t	size;
	t_pipex	*cmdline;
	t_pipex	*cmdhead;
	char	*cmdpath;

	cmdline = NULL;
	cmdpath = NULL;
	cmdhead = NULL;
	i = 0;
	size = get_outfile(cmd);
	while (cmd[i] && i < size)
	{
		cmdpath = get_cmdpath(get_envpath(env), ft_strtrim(cmd[i], WSP));
		cmdline = ft_lstnew(ft_strdup(cmd[i]), ft_getargs(cmd[i], cmdpath),
				cmdpath, ft_initpipe());
		if (!cmdline)
			return (ft_lstclear(&cmdhead), NULL);
		ft_lstadd_back(&cmdhead, cmdline);
		i++;
	}
	return (cmdhead);
}

t_pipex	*parse(char **str, char **env, int cmd)
{
	t_pipex	*pipe;

	pipe = NULL;
	pipe = create_linecmd((str + 1), env);
	if (!ft_findfiles(pipe, str))
		return (ft_lstclear(&pipe), ft_exit("Error: missing files \n"), NULL);
	return (pipe);
}
