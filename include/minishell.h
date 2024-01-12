/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:48:57 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/12 00:07:23 by picatrai         ###   ########.fr       */
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
# define ERROR_MALLOC 2


typedef struct s_data
{
    int fd_in;
    int fd_out;
}   t_data;

//ft_check_argc_envp.c
int ft_check_argc_envp(int argc, char **envp);


void    ft_put_prompt(char **envp);


//utils.c
void	ft_putstr_fd(char *s, int fd);
int ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, int n);
char	*find_path(char **envp, char *str);
int ft_occ(char *str, char c);

#endif