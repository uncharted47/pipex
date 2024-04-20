/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:01:39 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/20 01:52:21 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_setpipes(t_pipex *cmdline)
{
	while (cmdline)
	{
		pipe(cmdline->pipe);
		cmdline = cmdline->next;
	}
	
}

void	execute(t_pipex *cmdline, char **env)
{
	ft_setpipes(cmdline);
}