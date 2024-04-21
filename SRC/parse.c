/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:34:00 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/21 22:14:47 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**joinstr(char **str)
{
	size_t	i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	while (str[i])
		line = ft_strjoin(line, str[i++]);
	split = ft_split(line, WSP);
	return (free(line), split);
}

char	*get_cmdpath(char *path, char *cmd)
{
	char	**split;
	char	*line;
	char	*new;
	char	**cmdsplit;
	size_t	i;

	new = NULL;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) != -1)
		return (cmd);
	i = 0;
	cmdsplit = ft_split(cmd, WSP);
	new = ft_strjoin(ft_strdup("/"), cmdsplit[0]);
	split = ft_split((path + 5), ":");
	if (!split)
		return (perror("Error:"), free(new), free(cmdsplit), NULL);
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

int	isacmd(char *cmd)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

char	*ft_removepath(char *cmd)
{
	size_t	i;
	char	*str;
	char	*result;

	i = ft_strlen(cmd) - 1;
	str = ft_strdup(cmd);
	while (i && str[i] != '/')
		i--;
	result = ft_strdup(&str[i + 1]);
	return (free(str), result);
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

void	ft_initpipe(t_pipe **pipe)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	new->in = -1;
	new->out = -1;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	new->tmp = -1;
	*pipe = new;
}

t_pipex	*create_linecmd(char **cmd, char **env)
{
	size_t	i;
	size_t	size;
	t_pipex	*cmdline;
	t_pipex	*cmdhead;
	char	*cmdpath;
	t_pipe	*pipe;

	ft_initpipe(&pipe);
	cmdline = NULL;
	cmdpath = NULL;
	cmdhead = NULL;
	i = 0;
	size = get_outfile(cmd);
	while (cmd[i] && i < size)
	{
		cmdpath = get_cmdpath(get_envpath(env), ft_strtrim(cmd[i], WSP));
		cmdline = ft_lstnew(ft_strdup(cmd[i]), ft_getargs(cmd[i], cmdpath),
				cmdpath, pipe);
		if (!cmdline)
			return (ft_lstclear(&cmdhead), NULL);
		ft_lstadd_back(&cmdhead, cmdline);
		i++;
	}
	return (cmdhead);
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
	close(fd);
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

t_pipex	*parse(char **str, char **env, int cmd)
{
	t_pipex	*pipe;

	pipe = NULL;
	pipe = create_linecmd((str + 1), env);
	if (!ft_findfiles(pipe, str))
		return (ft_lstclear(&pipe), ft_exit("Error: missing files \n"), NULL);
	return (pipe);
}
