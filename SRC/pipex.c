/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:23:55 by elyzouli          #+#    #+#             */
/*   Updated: 2024/04/20 00:46:51 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int cmd, char *str[], char *env[])
{
	pid_t	id;
	int		i = 0;
	char	**split;
	// char *args[] = {"/usr/bin/ls","-la",NULL};

	// split = ft_split((char *)"test 1 25 ", " 2");
	parse(&str[1],env,cmd);
	// while(env[i])
	// 	printf("%s \n",env[i++]);
	// execve("/usr/bin/ls",args ,env);
	// id = fork();
	// i = 0;

	// while (split[i])
	// 	printf("%s \n", split[i++]);
	// if (id == 0)
	// {
	// 	printf("this is child  %d\n", id);
	// 	while (env[i])
	// 		printf("%s \n", env[i++]);
	// }
	// else
	// 	printf("this is parent %d \n", id);
	return (0);
}
