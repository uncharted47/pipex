/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:23:55 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/23 17:16:52 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int cmd, char *str[], char *env[])
{
	t_pipex	*head;

	head = parse(&str[1], env);
	if (ft_lstsize(head) != 2 && cmd != 5)
	{
		ft_lstclear(&head);
		ft_exit("Pipex : input must be 4 arguments \n");
		return (0);
	}
	execute(head, env);
	return (0);
}
