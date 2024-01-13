/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:48:57 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 22:07:25 by picatrai         ###   ########.fr       */
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

typedef struct s_data
{
    int fd_in;
    int fd_out;
}   t_data;

typedef struct s_token
{
    char *str;
    struct s_token *prev;
    struct s_token *next;
}   t_token;

//ft_check_argc_envp.c
int ft_check_argc_envp(int argc, char **envp);

//ft_get_prompt.c
char *ft_get_prompt(void);

//ft_parse.c
int ft_parse(t_token *token, char *input);

//ft_tokenisation_utils.c
int ft_is_quote_close(char *input, int double_quote_open, int single_quote_open);
int ft_size_malloc(char *input, int index, char c);

//utils.c
void	ft_putstr_fd(char *s, int fd);
int ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, int n);
int ft_occ(char *str, char c);
int ft_strchr(char *str, char *find);
char *ft_get_str(char *str);

//utils_2.c
t_token    *ft_lstlast(t_token *token);
t_token *ft_lstnew(char *str);
void    ft_lst_add_back(t_token **token, t_token *new);

#endif