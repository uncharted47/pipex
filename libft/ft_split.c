/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyzouli <elyzouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:46:04 by elyzouli          #+#    #+#             */
/*   Updated: 2023/11/11 09:37:25 by elyzouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *str, char sep)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (str[i] == '\0')
		return (count);
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			count++;
		while (str[i] && !(str[i] == sep))
			i++;
	}
	return (count);
}

static char	**failsafe(char **split, int flag)
{
	size_t	i;

	i = 0;
	if (flag)
	{
		split = (char **)malloc(sizeof(char *));
		if (!split)
			return (NULL);
		*split = NULL;
		return (split);
	}
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
	return (split);
}

static char	*ft_alloc(char *src, char sep)
{
	int		i;
	char	*split;
	int		sizeword;

	i = 0;
	sizeword = 0;
	while (src[sizeword] && !(sep == src[sizeword]))
		sizeword++;
	split = (char *)malloc(sizeof(char) * (sizeword + 1));
	if (!split)
		return (NULL);
	while (i < sizeword)
	{
		split[i] = src[i];
		i++;
	}
	split[i] = '\0';
	return (split);
}

static void	skipsepword(const char *str, char sep, int *i, int flag)
{
	if (flag)
	{
		while (str[*i] == sep)
			(*i)++;
	}
	else if (!flag)
	{
		while (str[*i] && str[*i] != sep)
			(*i)++;
	}
}

char	**ft_split(char const *str, char sep)
{
	int		i;
	int		k;
	char	**split;

	i = 0;
	k = 0;
	split = NULL;
	if (!str)
		return (failsafe(split, 1));
	split = (char **)malloc(sizeof(char *) * (ft_count_word(str, sep) + 1));
	if (!split)
		return (NULL);
	while (str && str[i])
	{
		skipsepword(str, sep, &i, 1);
		if (str[i])
		{
			split[k] = ft_alloc((char *)&str[i], sep);
			if (!split[k++])
				return (failsafe(split, 0));
		}
		skipsepword(str, sep, &i, 0);
	}
	split[k] = NULL;
	return (split);
}
