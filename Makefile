# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/03/12 21:50:59 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
INCLUDE = -I include
header = ./include/minishell.h

#  # ====================================================== #
#  |														|
#  |					OBJ_DIR								|
#  |														|
#  # ====================================================== #

dir_in_src = $(notdir $(shell find ./src/* -type d))

#  # ====================================================== #
#  |														|
#  |					  RULE								|
#  |														|
#  # ====================================================== #

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(header) | obj_dir_create
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

all: $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RFLAGS)

obj_dir_create:
	@if [ ! -d "./obj" ]; then\
		mkdir -p obj;\
	fi;\
	for d in $(dir_in_src); do\
		if [ ! -d ./obj/$$d ]; then\
			mkdir -p ./obj/$$d/;\
		fi;\
	done;\

clean:
	rm -rf $(OBJ) ./obj
	@echo "\033[1;33mAll objects have been deleted\033[0m\n"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;33mExecutable have been deleted\033[0m\n"

re: fclean all


.PHONY: all clean obj_dir_create
