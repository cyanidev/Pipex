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
//execve frees everything 0 = in 1 = out
static void	execute(char **argv, int n, char **envp)
{	
	char	*cmd_path;
	char	**cmd_options;

	cmd_path = path(argv[n], envp);
	cmd_options = options(argv[n]);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free(cmd_options);
		ret_error (argv[n]);
	}
	execve(cmd_path, cmd_options, envp);
}

static int	*create_files(char **argv)
{
	static int	files[2];

	files[0] = open(argv[1], O_RDONLY);
	if (files[0] == -1)
		ret_error(argv[1]);
	files[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (files[1] == -1)
		ret_error(argv[4]);
	return (files);
}

static void	child(int *fd, int *files, char **envp, char **argv)
{
	close(fd[0]);
	dup2(files[0], STDIN_FILENO);
	close(files[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute(argv, 2, envp);
}

static void	second_child(int *fd, int *files, char **envp, char **argv)
{
	close(fd[1]);
	close(files[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(files[1], STDOUT_FILENO);
	close(files[1]);
	execute(argv, 3, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		*files;
	int		status;

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
			second_child(fd, files, envp, argv);
		else if (pid == -1)
			ret_error("Error");
		else if (pid > 0)
			closefd(fd);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
