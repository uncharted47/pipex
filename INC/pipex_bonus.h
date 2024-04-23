/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:15:04 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 19:06:26 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define WSP " \t\n\f\r\v"

typedef struct s_args
{
	size_t			i;
	char			*tmp;
	char			*tmp2;
	char			**arr;
}					t_args;

typedef struct s_pipe
{
	int				pipe[2];
	int				out;
	int				tmp;
	int				in;
	int				fd;
}					t_pipe;

typedef struct s_pipex
{
	char			*cmd;
	char			**args;
	char			*file;
	int				fd;
	char			*delimiter;
	t_pipe			*pipe;
	char			*path;
	int				rd_wr;
	struct s_pipex	*next;

}					t_pipex;

//================LIBFT============================
int					ft_isalnum(int car);
int					ft_isalpha(int car);
int					ft_isdigit(int car);
char				**ft_split(char const *str, char *sep);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *str);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin2(char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlcat(char *dest, char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
t_pipex				*ft_lstnew(char *cmd, char **args, char *path,
						t_pipe *pipe);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(char *str, char *to_find, size_t n);
char				*ft_strrchr(char *str, int sub);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_lstadd_back(t_pipex **lst, t_pipex *new);
t_pipex				*ft_lstlast(t_pipex *lst);
char				*ft_strcat(char *dest, const char *src);
void				ft_lstadd_back(t_pipex **lst, t_pipex *new);
void				ft_lstdelone(t_pipex *lst);
char				**failsafe(char **split);
int					ft_lstsize(t_pipex *lst);
char				*ft_substr(char *s, unsigned int start, size_t len);
void				ft_lstclear(t_pipex **lst);
//==========================parsing==================
t_pipex				*create_linecmd(char **cmd, char **env);
t_pipex				*parse(char **str, char **env, int cmd);
char				*get_cmdpath(char *path, char *cmd);
char				*get_envpath(char **env);
size_t				get_outfile(char **cmd);
char				*ft_removepath(char *cmd);
int					ft_findfiles(t_pipex *cmdline, char **str);
int					is_sep(char c, char *sep);
char				*cmdpath_helper(char **split, char **cmdsplit, char *cmd,
						char *new);
t_pipex				*parse_heredoc(char **str, char **env, int cmd);
//=======================ERROR======================
void				ft_exit(char *message);
//===============excution=======================
void				execute(t_pipex *cmdline, char **env);
void				ft_cmdnotfound(char *cmd);
#endif