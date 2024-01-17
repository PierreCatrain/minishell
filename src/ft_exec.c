/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:14:09 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 00:54:35 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_exec(t_token *token)
{
    t_file file;
    char *str;

    file.fd_in = 0;
    file.fd_out = 1;
    while (token != NULL)
    {
        if (token->type == INFILE)
        {
            if (file.fd_in != 0)
                close(file.fd_in);
            file.fd_in = open(token->next->str, O_RDONLY, 0644);
            if (file.fd_in < 0)
                return ;
            dup2(file.fd_in, 0);
            token = token->next;
        }
        else if (token->type == OUTFILE)
        {
            if (file.fd_out != 1)
                close(file.fd_out);
            file.fd_out = open(token->next->str, O_WRONLY, 0644);
            if (file.fd_out < 0)
                return ;
            dup2(file.fd_out, 0);
            token = token->next;
        }
        else if (token->type == OUTFILE)
        {
            if (file.fd_out != 1)
                close(file.fd_out);
            file.fd_out = open(token->next->str, O_WRONLY, 0644);
            if (file.fd_out < 0)
                return ;
            dup2(file.fd_out, 0);
            token = token->next;
        }

        
        if (ft_strchr(token->str, "<<") == 1)
            token = ft_here_doc(token);
        else if (ft_strchr(token->str, ">>") == 1)
            token = ft_redirect_append_outfile(token);
        else if (ft_strchr(token->str, "<") == 1)
            token = ft_redirect_infile(token);
        else if (ft_strchr(token->str, ">") == 1)
            token = ft_redirect_outfile(token);
        else if (ft_strchr(token->str, "|") == 1)
            token = ft_pipes(token);
        else
            token = ft_cmd(token);
        if (token->next == NULL)
            break ;
        token = token->next;
    }
}