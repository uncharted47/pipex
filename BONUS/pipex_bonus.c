/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:23:55 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/22 16:58:49 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int cmd, char *str[], char *env[])
{
	pid_t	id;
	int		i;
	t_pipex	*head;

	i = 0;
	head = parse(&str[1], env, cmd);
	if (ft_lstsize(&head) != 2)
	{
		ft_lstclear(&head);
		ft_exit("Pipex : too many cmmands \n");
		return (0);
	}
	execute(head, env);
	return (0);
}
