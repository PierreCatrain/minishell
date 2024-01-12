# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/01/11 22:21:07 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRC = src/main.c src/ft_check_argc_envp.c src/ft_put_prompt.c src/ft_utils.c
OBJ = ${SRC:.c=.o}
INCLUDE = -I include

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $< ${INCLUDE}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} ${RFLAGS}

all: ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all