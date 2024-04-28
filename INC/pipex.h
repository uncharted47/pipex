/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:15:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/27 23:26:32 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define WSP " \t\n\f\r\v"
# define CMDNF "Pipex : Command not found "

typedef struct s_args
{
	size_t	i;
	char	*tmp;
	char	*tmp2;
	char	**arr;
}			t_args;
//==========================libft.h==================
size_t		ft_strlen(const char *s);
//==========================parsing==================
t_pipex		*parse(char **str, char **env);
char		*get_cmdpath(char *path, char *cmd);
char		*get_envpath(char **env);
size_t		get_outfile(char **cmd);
char		*ft_removepath(char *cmd);
int			ft_findfiles(t_pipex *cmdline, char **str);
int			is_sep(char c, char *sep);
char		*cmdpath_helper(char **split, char **cmdsplit, char *cmd,
				char *new);
//=======================ERROR======================
void		ft_exit(char *message);
void		ft_cmdnotfound(char *cmd, char *message);
void		isdir(char *cmd);
//===============excution=======================
int			execute(t_pipex *cmdline, char **env);
int			ft_exitstatus(t_pipex *cmdline, t_pipex *head, int fd);
int			ispath(char *cmd);
void		ft_close(int fd);
#endif