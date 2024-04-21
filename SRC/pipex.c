/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:23:55 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/21 18:31:55 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int cmd, char *str[], char *env[])
{
	pid_t	id;
	int		i;
	t_pipex	*split;

	i = 0;
	split = parse(&str[1], env, cmd);
	execute(split,env);
	return (0);
}
