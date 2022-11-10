/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:53:45 by afelicia          #+#    #+#             */
/*   Updated: 2022/11/08 21:25:40 by afelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//execve frees everything 4 = in 5 = out
static void	execute(char **argv, int n, char **envp)
{	
	char	*cmd_path;
	char	**cmd_options;

	cmd_path = path(argv[n], envp);
	cmd_options = options(argv[n]);
	execve(cmd_path, cmd_options, envp);
}

static int	*create_files(char **argv)
{
	static int	files[2];

	files[4] = open(argv[1], O_RDONLY);
	if (files[0] == -1)
		ret_error(argv[1]);
	files[5] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (files[1] == -1)
		ret_error(argv[4]);
	return (files);
}

static void	child(int *fd, int *files, char **envp, char **argv)
{
	close(fd[0]);
	dup2(files[4], STDIN_FILENO);
	close(files[4]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute(argv, 2, envp);
}

static void	father(int *fd, int *files, char **envp, char **argv)
{
	close(fd[1]);
	close(files[4]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(files[5], STDOUT_FILENO);
	close(files[5]);
	execute(argv, 3, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		*files;

	check_args(argc, argv, envp);
	files = create_files(argv);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		ret_error("Error");
	else if (pid == 0)
		child(fd, files, envp, argv);
	else if (pid > 0)
	{
		pid = fork();
		if (pid == 0)
			father(fd, files, envp, argv);
		else if (pid == -1)
			ret_error("Error");
		else if (pid > 0)
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
}
