# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/01/18 22:09:53 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRC = src/main.c \
src/ft_parse.c \
src/start/ft_check_argc_envp.c \
src/start/ft_get_prompt.c \
src/arbre_binaire/ft_create_tree.c \
src/arbre_binaire/ft_here_doc.c \
src/tokenisation/ft_condition_grammaire.c \
src/tokenisation/ft_isolate_operateur.c \
src/tokenisation/ft_replace_env_variable.c \
src/tokenisation/ft_set_all_grammaire.c \
src/tokenisation/ft_token_part_1.c \
src/tokenisation/ft_token_part_2.c \
src/tokenisation/ft_tokenisation.c \
src/utils/free.c \
src/utils/ft_utils.c \
src/utils/ft_utils_2.c \
src/utils/ft_utils_3.c \
src/utils/ft_utils_4.c

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