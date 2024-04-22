/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:15:16 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 16:49:04 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstadd_back(t_pipex **lst, t_pipex *new)
{
	t_pipex	*last;

	if (!lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstdelone(t_pipex *lst)
{
	if (!lst)
		return ;
	free(lst->cmd);
	free(lst->path);
	failsafe(lst->args);
	free(lst);
	lst = NULL;
}

void	ft_lstclear(t_pipex **lst)
{
	t_pipex	*tmp;
	int		i;

	i = 0;
	if (!lst || !(*lst))
		return ;
	tmp = (*lst);
	if (tmp->pipe)
		free(tmp->pipe);
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = tmp;
		tmp = NULL;
	}
}

int	ft_lstsize(t_pipex *lst)
{
	int	i;

	i = 0;
	while (lst && ++i)
		lst = lst->next;
	return (i);
}

t_pipex	*ft_lstnew(char *cmd, char **args, char *path, t_pipe *pipe)
{
	t_pipex	*node;

	node = (t_pipex *)malloc(sizeof(t_pipex));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->args = args;
	node->path = path;
	node->pipe = pipe;
	node->fd = -1;
	node->rd_wr = 0;
	node->next = NULL;
	return (node);
}
