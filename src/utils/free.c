/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/27 16:11:29 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_free_token(t_token **token)
{
    t_token *tmp;

    while ((*token)->prev != NULL)
        *token = (*token)->prev;
    while(*token != NULL)
    {
        free((*token)->str);
        tmp = *token;
        *token = (*token)->next;
        free(tmp);
    }
}

void free_tokenisation_2(char *input, t_token **token, t_data_parse *data_parse)
{
    t_token *tmp;
    
    free(input);
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
        if (str[index] != NULL)
            free(str[index]);
    }
    //free(str);
}

void free_exec_list(t_lst_exec *exec)
{
    t_lst_exec *tmp;
    
    while (exec != NULL)
    {
        tmp = exec;
        free(exec->cmd);
        free_2d(exec->args);
        exec = exec->next;
        free(tmp);
    }
}

void free_tree(t_tree *tree)
{
    if (tree->left_child != NULL)
        free_tree(tree->left_child);
    if (tree->right_child != NULL)
        free_tree(tree->right_child);
    if (tree->lst_exec != NULL)
        free_exec_list(tree->lst_exec);
    free(tree);
    return ;
}