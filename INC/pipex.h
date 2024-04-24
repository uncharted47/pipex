/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:15:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 16:37:56 by elyzouli         ###   ########.fr       */
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
//===============excution=======================
int			execute(t_pipex *cmdline, char **env);
void		ft_cmdnotfound(char *cmd);
#endif