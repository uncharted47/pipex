/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:23:55 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/24 02:16:14 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int cmd, char *str[], char *env[])
{
	t_pipex	*head;
	int		status;

	if (!ft_strncmp("here_doc", str[1], ft_strlen("here_doc"))
		&& ft_strlen("here_doc") == ft_strlen(str[1]))
	{
		head = parse_heredoc(&str[2], env, cmd);
		status = execute_heredoc(head, env);
	}
	else
	{
		head = parse(&str[1], env, cmd);
		status = execute(head, env);
	}
	return (status);
}
