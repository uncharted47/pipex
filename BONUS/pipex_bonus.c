/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:23:55 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 16:42:18 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int cmd, char *str[], char *env[])
{
	t_pipex	*head;

	if (!ft_strncmp("here_doc", str[1], ft_strlen("here_doc")))
		head = parse_heredoc(&str[2], env,cmd);
	else
		head = parse(&str[1], env,cmd);
	execute(head, env);
	return (0);
}
