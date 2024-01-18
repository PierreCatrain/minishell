# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/01/17 20:50:28 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRC = src/main.c src/ft_check_argc_envp.c src/ft_get_prompt.c src/ft_parse.c \
src/ft_utils.c src/ft_utils_2.c src/ft_utils_3.c src/ft_utils_4.c src/ft_tokenisation.c src/ft_token_part_1.c src/ft_token_part_2.c src/free.c \
src/ft_isolate_operateur.c src/ft_replace_env_variable.c src/ft_create_tree.c src/ft_here_doc.c src/ft_set_all_grammaire.c src/ft_condition_grammaire.c
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