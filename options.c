/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:09:04 by afelicia          #+#    #+#             */
/*   Updated: 2022/11/09 22:17:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**options(char *cmd)
{	
	int		i;
	char	**option_vector;

	i = 0;
	while (ft_isspace(cmd[i]))
	{
		i++;
	}
	option_vector = ft_split_options(&cmd[i]);
	if (option_vector == NULL)
	{
		ret_error("program ran out of memory");
	}
	return (option_vector);
}
