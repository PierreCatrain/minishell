/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_all_grammaire.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:13:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/30 00:48:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// on s'assure que les quotes ouvertes sont bien ferme sinon l'input n'est pas traitable
int ft_is_quote_close(char *input, int double_quote_open, int single_quote_open)
{
    int index;

    index = 0;
    while (input[index])
    {
        if (input[index] == '"')
            double_quote_open = OPEN;
        else if (input[index] == '\'')
            single_quote_open = OPEN;
        index++;
        while (double_quote_open == OPEN && input[index])
        {
            if (input[index++] == '"')
                double_quote_open = CLOSE;
        }
        while (single_quote_open == OPEN && input[index])
        {
            if (input[index++] == '\'')
                single_quote_open = CLOSE;
        }
    }
    if (double_quote_open == OPEN || single_quote_open == OPEN)
        return (ft_putstr_fd("minishell: syntax error with open quotes\n", 2), OPEN);
    return (CLOSE);
}

// on defini le type de tout les textes qui suivient des operateurs de redirections
// puis on defini le type de tout le reste soit les cmd suivi d'args
void ft_set_all_grammaire(t_token **token)
{
    while ((*token)->next != NULL)
    {
        if ((*token)->type == INFILE && (*token)->next->type == TEXT)
        {
            *token = (*token)->next;
            (*token)->type = INFILE_TEXT;
        }
        else if ((*token)->type == OUTFILE && (*token)->next->type == TEXT)
        {
            *token = (*token)->next;
            (*token)->type = OUTFILE_TEXT;
        }
        else if ((*token)->type == HEREDOC && (*token)->next->type == TEXT)
        {
            *token = (*token)->next;
            (*token)->type = HEREDOC_TEXT;
        }
        else if ((*token)->type == APPEND && (*token)->next->type == TEXT)
        {
            *token = (*token)->next;
            (*token)->type = APPEND_TEXT;
        }
        if ((*token)->next == NULL)
            break;
        *token = (*token)->next;
    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
    while ((*token)->next != NULL)
    {
        if ((*token)->type == TEXT)
        {
            (*token)->type = CMD;
            if ((*token)->next == NULL)
                break;
            *token = (*token)->next;
            while ((*token)->type == TEXT)
            {
                (*token)->type = ARGS;
                if ((*token)->next == NULL)
                    break;
                *token = (*token)->next;
            }
        }
        else
        {
            if ((*token)->next == NULL)
                break;
            *token = (*token)->next;
        }
    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
}