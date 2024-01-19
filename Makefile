# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/01/19 06:20:49 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
INCLUDE = -I include

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)
	@echo "\033[1;32m COMPILED \033[1;37m->\033[4;32m $< \033[0m"

$(NAME): $(OBJ)
	@echo "\n\033[1;33mAll objects have been created\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RFLAGS)

all: $(OBJDIR) $(NAME)

clean:
	rm -f $(OBJ)
	@echo "\033[1;33mAll objects have been deleted\033[0m\n"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;33mExecutable have been deleted\033[0m\n"

re: fclean all

.PHONY: all clean
