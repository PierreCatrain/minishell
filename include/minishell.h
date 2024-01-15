/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:48:57 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/15 00:56:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define ERROR_ARGC_ENVP 1
# define ERROR_PROMPT 2
# define ERROR_MALLOC 3
# define GOOD_INPUT 0
# define WRONG_INPUT 1
# define WD_BUFFER_SIZE 5000
# define OPEN 0
# define CLOSE 1
# define WORD 1
# define SINGLE_QUOTES 2
# define DOUBLE_QUOTES 3
# define START_DOLLAR 0
# define NOT_START_DOLLAR 1

typedef struct s_data
{
    int fd_in;
    int fd_out;
}   t_data;

typedef struct s_token
{
    char *str;
    int type;
    struct s_token *prev;
    struct s_token *next;
}   t_token;

typedef struct s_data_token
{
    int double_quote_open;
    int single_quote_open;
    int new_word;
    int index_str;
    int index;
    char *str;
}   t_data_token;

//ft_check_argc_envp.c
int ft_check_argc_envp(int argc, char **envp);

//ft_get_prompt.c
char *ft_get_prompt(void);

//ft_parse.c
int ft_parse(t_token **token, char *input);

//ft_tokenisation.c
int ft_tokenisation(t_token **token, char *input);

//ft_token_part_1.c
int ft_token_part_1(char *input, t_data_token *data_token, t_token **token);

//ft_token_part_2.c
int ft_token_part_2(char *input, t_data_token *data_token, t_token **token);

//ft_replace_env_variable.c
int     ft_replace_env_variable(t_token **token);

//utils.c
void	ft_putstr_fd(char *s, int fd);
int ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, int n);
int ft_occ(char *str, char c);
int ft_strchr(char *str, char *find);

//utils_2.c
char *ft_strdup(char *str);
t_token    *ft_lstlast(t_token *token);
t_token *ft_lstnew(char *str, int type);
int    ft_lst_add_back(t_token **token, t_token *new);
char *ft_get_str(char *str);

//utils_3.c
int	ft_lstsize(t_token *token);
void    ft_print_token(t_token **token);
int	ft_isalphanum(int c);

//free.c
void ft_free_token(t_token **token);
void free_tokenisation_1(char *input, t_token **token);
void free_tokenisation_2(char *input, t_token **token, t_data_token *data_token);

#endif

/*
    ERREUR
    "'$USER '"
    '' -> segfault
    """"
    export [] = /&*()!@#$%
*/