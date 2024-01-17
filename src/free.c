/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 05:45:16 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_free_token(t_token **token)
{
    t_token *tmp;

    while(*token != NULL)
    {
        free((*token)->str);
        tmp = *token;
        *token = (*token)->next;
        free(tmp);
    }
}

void free_tokenisation_2(char *input, t_token **token, t_data_token *data_token)
{
    t_token *tmp;
    
    free(input);
    free(data_token->str);
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
    
    index = -1;
    while (str[++index])
        free(str[index]);
    free(str);
}