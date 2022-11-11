/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:02:58 by marvin            #+#    #+#             */
/*   Updated: 2022/11/10 14:02:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc < 5)
		return (ret_error("Error: too few arguments. Try: ./pipex file1 cmd1 "
				"cmd2 file2"));
	if (!envp || envp[0][0] == '\0')
		ret_error("envp invalid");
}

void	closefd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	waitstatus(int status)
{
	wait(&status);
	wait(&status);
}