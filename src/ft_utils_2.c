/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 02:20:28 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token    *ft_lstlast(t_token *token)
{
    if (token == NULL)
        return (NULL);
    while (token->next != NULL)
        token = token->next;
    return (token);
}

t_token *ft_lstnew(char *str)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (new == NULL)
        return (NULL);
    new->str = str;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

void    ft_lst_add_back(t_token **token, t_token *new)
{
    if (*token == NULL)
        *token = new;
    else
        ft_lstlast(*token)->next = new;
}