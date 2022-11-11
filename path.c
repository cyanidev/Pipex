/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:55:22 by afelicia          #+#    #+#             */
/*   Updated: 2022/11/11 00:47:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_cmd_size(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_isspace(cmd[i]))
		i++;
	while (!ft_isspace(cmd[i]) && cmd[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static void	cmd_cpy(char *cmd, char *cmd_trim)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(cmd[i]))
		i++;
	while (!ft_isspace(cmd[i]) && cmd[i] != '\0')
	{
		cmd_trim[j] = cmd[i];
		j++;
		i++;
	}
	cmd_trim[j] = '\0';
}

static char	*testing(char **paths, char *cmd)
{
	char	*test;
	int		i;
	int		cmd_size;
	char	*cmd_trim;

	cmd_size = get_cmd_size(cmd);
	cmd_trim = malloc(cmd_size * sizeof(char) + 1);
	if (cmd_trim == NULL)
		return (NULL);
	cmd_cpy(cmd, cmd_trim);
	i = 0;
	while (paths[i] != NULL)
	{
		test = ft_strjoin(paths[i++], cmd_trim);
		if (test == NULL)
			ret_error("program ran out of memory");
		else if (access(test, F_OK | X_OK) == 0)
		{
			free(cmd_trim);
			return (test);
		}
		free(test);
	}
	free(cmd_trim);
	return (NULL);
}

void	ret_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

char	*path(char *cmd, char **envp)
{
	char	*path_envp;
	char	**paths;
	int		i;
	char	*test;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (envp[i] == NULL)
		ret_error("no path in env");
	path_envp = envp[i];
	paths = ft_splitpath(&path_envp[5], ':');
	if (paths == NULL)
		ret_error("program ran out of memory");
	test = testing(paths, cmd);
	ft_free(paths);
	return (test);
}
