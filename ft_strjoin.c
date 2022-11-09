/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:20:34 by afelicia          #+#    #+#             */
/*   Updated: 2022/10/16 17:21:18 by afelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*snew;
	size_t	i;
	size_t	j;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	snew = malloc(sizeof(char) * (len + 1));
	if (snew == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		snew[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		snew[i + j] = s2[j];
		j++;
	}
	snew[i + j] = '\0';
	return (snew);
}
