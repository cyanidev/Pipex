# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 16:57:15 by afelicia          #+#    #+#              #
#    Updated: 2022/11/10 18:43:31 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =	ft_splitpath.c \
		ft_strncmp.c \
		ft_calloc.c \
		ft_strjoin.c \
		path.c \
		ft_isspace.c \
		options.c \
		ft_split_options.c \
		main.c \
		checkargs.c \
		ft_strlen.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -O0

RM = rm -f

${NAME} : ${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:	
		${RM} ${OBJS}

all: ${NAME}

fclean: clean 
			${RM} ${NAME}
re: fclean all

.PHONY: all clean fclean re

