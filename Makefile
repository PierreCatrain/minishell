# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/02/26 16:54:54 by lgarfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#  # ====================================================== #
#  |														|
#  |			 CONSOLE_DESIGN								|
#  |														|
#  # ====================================================== #

WHITE=$'\033[0;37m
GREY=$'\033[0;30m
RED=$'\033[0;31m
GREEN=$'\033[0;32m
YELLOW=$'\033[0;33m
CYAN=$'\033[0;34m
PURPLE=$'\033[0;35m
DEF_COLOR = \033[0;39m

#  # ====================================================== #
#  |														|
#  |				   VARIABLE								|
#  |														|
#  # ====================================================== #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
INCLUDE = -I include
INCLUDE_LIBFT = 
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
	@echo "\033[1;32m COMPILED \033[1;37m->\033[4;32m $< \033[0m"

all: $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RFLAGS)
	@echo "\n\033[1;33mAll objects have been created\033[0m"
	@clear
	@./minishell

valgrind:  $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RFLAGS)
	@echo "\n\033[1;33mAll objects have been created\033[0m"
	@clear
	@valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./minishell

env less:  $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RFLAGS)
	@echo "\n\033[1;33mAll objects have been created\033[0m"
	@clear
	@env -i ./minishell

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
