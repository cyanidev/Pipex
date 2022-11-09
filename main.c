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

static void	check_args(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc < 5)
		return (ret_error("Error: too few arguments. Try: ./pipex file1 cmd1 "
				"cmd2 file2"));
	if (!envp || envp[0][0] == '\0')
		ret_error("envp invalid");
}

static void	child1(int *fd, char **argv)
{
	int	fdin;

	close(fd[0]);
	fdin = open(argv[1], O_RDONLY);
	if (fdin == -1)
		ret_error(argv[1]);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

static void	child2(int	*fd, char **argv)
{
	int	fdout;

	close(fd[1]);
	fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fdout == -1)
	{
		ret_error(argv[4]);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

static void	second_fork(int *fd, char **argv, char *cmd_path,
	char **cmd_options)
{
	pid_t		pid;
	extern char	**environ;

	pid = fork();
	if (pid == 0)
	{
		child2(fd, argv);
		execve(cmd_path, cmd_options, environ);
	}
	else if (pid == -1)
		ret_error("Error");
	else if (pid > 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	*cmd_path;
	char	**cmd_options;

	check_args(argc, argv, envp);
	pipe(fd);
	cmd_path = path(argv[2], envp);
	cmd_options = options(argv[2]);
	pid = fork();
	if (pid == -1)
		ret_error("Error");
	else if (pid == 0)
	{
		child1(fd, argv);
		execve(cmd_path, cmd_options, envp);
	}
	else if (pid > 0)
	{
		free(cmd_path);
		free(cmd_options);
		cmd_path = path(argv[3], envp);
		cmd_options = options(argv[3]);
		second_fork(fd, argv, cmd_path, cmd_options);
	}
}
