/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:32 by afelicia          #+#    #+#             */
/*   Updated: 2022/11/09 22:16:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	word_count(const char *str)
{
	size_t	count;
	size_t	flag;
	size_t	i;

	count = 0;
	flag = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (!ft_isspace(str[i]) && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (ft_isspace(str[i]))
			flag = 0;
		i++;
	}
	return (count);
}

static char	*ft_word(const char *str, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(sizeof(char) * ((end - start) + 1));
	if (word == NULL)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_options(char const *s)
{
	size_t	i;
	size_t	j;
	ssize_t	start;
	char	**result;

	result = ft_calloc(sizeof(char *), (word_count(s) + 1));
	i = 0;
	j = 0;
	start = -1;
	if (result == NULL || s == NULL)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (!ft_isspace(s[i]) && start < 0)
			start = (ssize_t)i;
		else if ((ft_isspace(s[i]) || i == ft_strlen(s)) && start >= 0)
		{
			result[j++] = ft_word(s, (size_t)start, i);
			if (result[j - 1] == NULL)
				return (ft_free(result));
			start = -1;
		}
		i++;
	}
	return (result);
}
