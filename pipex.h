/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:10:44 by afelicia          #+#    #+#             */
/*   Updated: 2022/11/10 14:03:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>

char	**ft_splitpath(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_free(char **split);
void	*ft_calloc(size_t count, size_t size);
void	ret_error(char *error_msg);
int		ft_isspace(int c);
char	**options(char *cmd);
char	**ft_split_options(char const *s);
void	check_args(int argc, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);

#endif
