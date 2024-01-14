/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 04:42:50 by picatrai         ###   ########.fr       */
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

t_token *ft_lstnew(char *str, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (new == NULL)
        return (NULL);
    new->str = ft_strdup(str);
    if (new->str == NULL)
        return (free(new), NULL);
    free(str);
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

char *ft_get_str(char *str)
{
    return (str);
}