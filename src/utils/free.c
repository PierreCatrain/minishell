/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/01 01:29:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_free_token(t_token **token)
{
    t_token *tmp;

    if (*token == NULL)
        return ;
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
    while(*token != NULL)
    {
        if ((*token)->str != NULL)
            free((*token)->str);
        tmp = *token;
        *token = (*token)->next;
        free(tmp);
    }
}

void free_tokenisation_2(t_token **token, t_data_parse *data_parse)
{
    t_token *tmp;
    
    ft_print_error_malloc();
    free(data_parse->input);
    free(data_parse->str);
    while(token != NULL)
    {
        free((*token)->str);
        tmp = *token;
        *token = (*token)->next;
        free(tmp);
    }
}

void free_tokenisation_1(char *input, t_token **token)
{
    t_token *tmp;
    
    ft_print_error_malloc();
    free(input);
    while(token != NULL)
    {
        free((*token)->str);
        tmp = *token;
        *token = (*token)->next;
        free(tmp);
    }
}

void    free_2d(char **str)
{
    int index;

    if (str == NULL || str[0] == NULL)
        return ;
    index = -1;
    while (str[++index])
    {
        if (str[index] != NULL && str[index][0] != '\0')
            free(str[index]);
    }
    free(str);
}

void free_close_exec_list(t_lst_exec *exec)
{
    t_lst_exec *tmp;
    
    while (exec != NULL)
    {
        tmp = exec;
        free_2d(exec->args);
        if (exec->fd_in > 2)
            close(exec->fd_in);
        if (exec->fd_out > 2)
            close(exec->fd_out);
        exec = exec->next;
        free(tmp);
    }
}

void free_close_tree(t_tree *tree)
{
    if (tree->left_child != NULL)
        free_close_tree(tree->left_child);
    if (tree->right_child != NULL)
        free_close_tree(tree->right_child);
    if (tree->lst_exec != NULL)
        free_close_exec_list(tree->lst_exec);
    free(tree);
    return ;
}

void ft_print_error_malloc(void)
{
    printf("minishell: malloc failed\n");
}