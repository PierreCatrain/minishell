/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/29 19:56:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_strdup(char *str)
{
    char *new;
    int index;

    new = malloc((ft_strlen(str) + 1) * sizeof(char));
    if (new == NULL)
        return (NULL);
    index = -1;
    while (str[++index])
        new[index] = str[index];
    new[index] = '\0';
    return (new);
}

t_token    *ft_lstlast(t_token *token)
{
    if (token == NULL)
        return (NULL);
    while (token->next != NULL)
        token = token->next;
    return (token);
}

t_token *ft_lstnew(char *str, int quotes, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (new == NULL)
        return (NULL);
    new->str = ft_strdup(str);
    if (new->str == NULL)
        return (free(new), NULL);
    free(str);
    new->quotes = quotes;
    new->type = type;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

int    ft_lst_add_back(t_token **token, t_token *new)
{
    if (new == NULL)
        return (ERROR_MALLOC);
    if (*token == NULL)
        *token = new;
    else
    {
        new->prev = ft_lstlast(*token);
        ft_lstlast(*token)->next = new;
    }
    return (SUCCESS);
}

int ft_lst_insert(t_token **token, t_token *new)
{
    if (new == NULL)
        return (ERROR_MALLOC);
    if (*token == NULL)
        *token = new;
    else
    {
        if ((*token)->next != NULL)
        {
            (*token)->next->prev = new;
            new->next = (*token)->next;
        }
        (*token)->next = new;
        new->prev = *token;
    }
    return (SUCCESS);
}

void ft_lst_del(t_token **token)
{
    t_token *tmp;
    
    tmp = *token;
    if ((*token)->next != NULL && (*token)->prev != NULL)
    {
        (*token)->next->prev = (*token)->prev;
        (*token)->prev->next = (*token)->next;
        *token = (*token)->next;
        free(tmp->str);
        free(tmp);
    }
    else if ((*token)->next != NULL)
    {
        (*token)->next->prev = NULL;
        *token = (*token)->next;
        free(tmp->str);
        free(tmp);
    }
    else if ((*token)->prev != NULL)
    {
        (*token)->prev->next = NULL;
        *token = (*token)->prev;
        free(tmp->str);
        free(tmp);
    }
}

char *ft_get_str(char *str)
{
    return (str);
}