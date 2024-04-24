/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:15:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 18:32:28 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define WSP " \t\n\f\r\v"

typedef struct s_args
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	**arr;
	int		fd;
}			t_args;

//==========================parsing==================
t_pipex		*create_linecmd(char **cmd, char **env);
t_pipex		*parse(char **str, char **env, int cmd);
char		*get_cmdpath(char *path, char *cmd);
char		*get_envpath(char **env);
size_t		get_outfile(char **cmd);
char		*ft_removepath(char *cmd);
int			ft_findfiles(t_pipex *cmdline, char **str);
int			is_sep(char c, char *sep);
char		*cmdpath_helper(char **split, char **cmdsplit, char *cmd,
				char *new);
t_pipex		*parse_heredoc(char **str, char **env, int cmd);
//=======================ERROR======================
void		ft_exit(char *message);
//===============excution=======================
int			execute(t_pipex *cmdline, char **env);
void		ft_cmdnotfound(char *cmd);
char		*pipecount(t_pipex *cmdline);
void		ft_readheredoc(t_pipex *cmdline);
int			execute_heredoc(t_pipex *cmdline, char **env);
#endif