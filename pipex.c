/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:43:01 by afelicia          #+#    #+#             */
/*   Updated: 2022/11/09 22:26:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*pathfinder(char *test, char **paths, char *path_envp, char *cmd)
{
	int	i;

	path_envp = envp[i];
	i = 0;
	paths = ft_splitpath(&path_envp[5], ':');
	while (paths[i] != NULL)
	{
		test = ft_strjoin(paths[i++], cmd);
		if (access(test, F_OK | X_OK) == 0)
		{
			free (test);
			ft_free(paths);
			return (test);
		}
		free (test);
	}
	ft_free(paths);
	return (0);
}

char	*pipex(char *cmd, char **envp)
{
	char	*path_envp;
	char	**paths;
	int		i;
	char	*test;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i++], "PATH=", 5))
			break ;
	}
	if (envp[i] == NULL)
	{
		printf("no path in env");
		return (0);
	}
	return (pathfinder(test, paths, path_envp, cmd));
}
