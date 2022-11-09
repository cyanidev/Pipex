/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:11:15 by afelicia          #+#    #+#             */
/*   Updated: 2022/10/16 18:13:33 by afelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	imemset(char *ptr, int c, size_t size)
{
	if (size > 1)
		imemset(ptr + 1, c, size - 1);
	if (size)
		*ptr = (char)c;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && ((SIZE_MAX / count) < size))
		return (NULL);
	ptr = malloc(count * size);
	if (ptr)
		imemset(ptr, 0, count * size);
	return (ptr);
}
