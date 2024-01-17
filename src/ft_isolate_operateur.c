/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isolate_operateur.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:32:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 02:36:15 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token *ft_lstnew_no_malloc(char *str, int quotes, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (new == NULL)
        return (NULL);
    new->str = ft_strdup(str);
    if (new->str == NULL)
        return (free(new), NULL);
    new->quotes = quotes;
    new->type = type;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

char *ft_str_rev(char *str)
{
    char *new_str;
    int index;
    int index_new_str;

    new_str = malloc ((ft_strlen(str) + 1) * sizeof(char));
    if (new_str == NULL)
        return (free(str), NULL);
    index = ft_strlen(str);
    index_new_str = 0;
    while (--index >= 0)
        new_str[index_new_str++] = str[index];
    new_str[index_new_str] = '\0'; 
    return (free(str), new_str);
}

int ft_insert_operateur(t_token **token)
{
    int index;
    int index_new_str;
    char *str;

    str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
    if (str == NULL)
        return (ERROR_MALLOC);
    index = ft_strlen((*token)->str);
    index_new_str = 0;
    while (--index >= 0 && (*token)->quotes == WORD)
    {
        if ((*token)->str[index - 1] == '<' && (*token)->str[index] == '<')
        {
            str[index_new_str] = '\0';
            str = ft_str_rev(str);
            if (str == NULL)
                return (ERROR_MALLOC);
            ft_lst_insert(token, ft_lstnew(str, WORD, HEREDOC));
            ft_lst_insert(token, ft_lstnew_no_malloc("<<", WORD, HEREDOC));
            str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
            if (str == NULL)
                return (ERROR_MALLOC);
            index_new_str = 0;
            index--;
        }
        else if ((*token)->str[index - 1] == '>' && (*token)->str[index] == '>')
        {
            str[index_new_str] = '\0';
            str = ft_str_rev(str);
            if (str == NULL)
                return (ERROR_MALLOC);
            ft_lst_insert(token, ft_lstnew(str, WORD, APPEND));
            ft_lst_insert(token, ft_lstnew_no_malloc(">>", WORD, APPEND));
            str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
            if (str == NULL)
                return (ERROR_MALLOC);
            index_new_str = 0;
            index--;
        }
        else if ((*token)->str[index] == '<')
        {
            str[index_new_str] = '\0';
            str = ft_str_rev(str);
            if (str == NULL)
                return (ERROR_MALLOC);
            ft_lst_insert(token, ft_lstnew(str, WORD, INFILE));
            ft_lst_insert(token, ft_lstnew_no_malloc("<", WORD, INFILE));
            str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
            if (str == NULL)
                return (ERROR_MALLOC);
            index_new_str = 0;
        }
        else if ((*token)->str[index] == '>')
        {
            str[index_new_str] = '\0';
            str = ft_str_rev(str);
            if (str == NULL)
                return (ERROR_MALLOC);
            ft_lst_insert(token, ft_lstnew(str, WORD, OUTFILE));
            ft_lst_insert(token, ft_lstnew_no_malloc(">", WORD, OUTFILE));
            str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
            if (str == NULL)
                return (ERROR_MALLOC);
            index_new_str = 0;
        }
        else if ((*token)->str[index] == '|')
        {
            str[index_new_str] = '\0';
            str = ft_str_rev(str);
            if (str == NULL)
                return (ERROR_MALLOC);
            ft_lst_insert(token, ft_lstnew(str, WORD, PIPE));
            ft_lst_insert(token, ft_lstnew_no_malloc("|", WORD, PIPE));
            str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
            if (str == NULL)
                return (ERROR_MALLOC);
            index_new_str = 0;
        }
        else
            str[index_new_str++] = (*token)->str[index];
    }
    str[index_new_str] = '\0';
    (*token)->str = ft_str_rev(str);
    if ((*token)->str == NULL)
        return (ERROR_MALLOC);
    return (SUCCESS);
}

int ft_isolate_operateur(t_token **token)
{
    while (*token != NULL)
    {
        if ((*token)->quotes == WORD && (*token)->type == TEXT)
            ft_insert_operateur(token);
        if ((*token)->next == NULL)
            break ;
        else
            *token = (*token)->next;
    }
    while (token != NULL)
    {
        if ((*token)->prev == NULL)
            break ;
        else
            *token = (*token)->prev;
    }
    while (*token != NULL)
    {
        if ((*token)->str[0] == '\0')
            ft_lst_del(token);
        if ((*token)->next == NULL)
            break ;
        else
            *token = (*token)->next;
    }
    return (SUCCESS);
}